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

/* Variables and functions */
 unsigned char* adj_for_padding (unsigned char*,unsigned char*,size_t) ; 
 unsigned char* intel_pt_find_overlap_tsc (unsigned char*,size_t,unsigned char*,size_t,int*) ; 
 int /*<<< orphan*/  intel_pt_next_psb (unsigned char**,size_t*) ; 
 int /*<<< orphan*/  intel_pt_step_psb (unsigned char**,size_t*) ; 
 unsigned char* memmem (unsigned char*,size_t,unsigned char*,size_t) ; 

unsigned char *intel_pt_find_overlap(unsigned char *buf_a, size_t len_a,
				     unsigned char *buf_b, size_t len_b,
				     bool have_tsc, bool *consecutive)
{
	unsigned char *found;

	/* Buffer 'b' must start at PSB so throw away everything before that */
	if (!intel_pt_next_psb(&buf_b, &len_b))
		return buf_b + len_b; /* No PSB */

	if (!intel_pt_next_psb(&buf_a, &len_a))
		return buf_b; /* No overlap */

	if (have_tsc) {
		found = intel_pt_find_overlap_tsc(buf_a, len_a, buf_b, len_b,
						  consecutive);
		if (found)
			return found;
	}

	/*
	 * Buffer 'b' cannot end within buffer 'a' so, for comparison purposes,
	 * we can ignore the first part of buffer 'a'.
	 */
	while (len_b < len_a) {
		if (!intel_pt_step_psb(&buf_a, &len_a))
			return buf_b; /* No overlap */
	}

	/* Now len_b >= len_a */
	while (1) {
		/* Potential overlap so check the bytes */
		found = memmem(buf_a, len_a, buf_b, len_a);
		if (found) {
			*consecutive = true;
			return adj_for_padding(buf_b + len_a, buf_a, len_a);
		}

		/* Try again at next PSB in buffer 'a' */
		if (!intel_pt_step_psb(&buf_a, &len_a))
			return buf_b; /* No overlap */
	}
}