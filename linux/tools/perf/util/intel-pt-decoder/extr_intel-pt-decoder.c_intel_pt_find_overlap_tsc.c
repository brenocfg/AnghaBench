#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 unsigned char* adj_for_padding (unsigned char*,unsigned char*,size_t) ; 
 unsigned char* intel_pt_last_psb (unsigned char*,size_t) ; 
 scalar_t__ intel_pt_next_tsc (unsigned char*,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  intel_pt_step_psb (unsigned char**,size_t*) ; 
 int intel_pt_tsc_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *intel_pt_find_overlap_tsc(unsigned char *buf_a,
						size_t len_a,
						unsigned char *buf_b,
						size_t len_b, bool *consecutive)
{
	uint64_t tsc_a, tsc_b;
	unsigned char *p;
	size_t len, rem_a, rem_b;

	p = intel_pt_last_psb(buf_a, len_a);
	if (!p)
		return buf_b; /* No PSB in buf_a => no overlap */

	len = len_a - (p - buf_a);
	if (!intel_pt_next_tsc(p, len, &tsc_a, &rem_a)) {
		/* The last PSB+ in buf_a is incomplete, so go back one more */
		len_a -= len;
		p = intel_pt_last_psb(buf_a, len_a);
		if (!p)
			return buf_b; /* No full PSB+ => assume no overlap */
		len = len_a - (p - buf_a);
		if (!intel_pt_next_tsc(p, len, &tsc_a, &rem_a))
			return buf_b; /* No TSC in buf_a => assume no overlap */
	}

	while (1) {
		/* Ignore PSB+ with no TSC */
		if (intel_pt_next_tsc(buf_b, len_b, &tsc_b, &rem_b)) {
			int cmp = intel_pt_tsc_cmp(tsc_a, tsc_b);

			/* Same TSC, so buffers are consecutive */
			if (!cmp && rem_b >= rem_a) {
				unsigned char *start;

				*consecutive = true;
				start = buf_b + len_b - (rem_b - rem_a);
				return adj_for_padding(start, buf_a, len_a);
			}
			if (cmp < 0)
				return buf_b; /* tsc_a < tsc_b => no overlap */
		}

		if (!intel_pt_step_psb(&buf_b, &len_b))
			return buf_b + len_b; /* No PSB in buf_b => no data */
	}
}