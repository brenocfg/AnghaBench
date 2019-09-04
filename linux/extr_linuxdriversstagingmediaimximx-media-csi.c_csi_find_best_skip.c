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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct v4l2_fract {scalar_t__ numerator; scalar_t__ denominator; } ;
struct csi_skip_desc {scalar_t__ max_ratio; int keep; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ARRAY_SIZE (struct csi_skip_desc*) ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ USEC_PER_SEC ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  csi_apply_skip_interval (struct csi_skip_desc const*,struct v4l2_fract*) ; 
 struct csi_skip_desc* csi_skip ; 
 scalar_t__ div_u64 (scalar_t__,int) ; 

__attribute__((used)) static const struct csi_skip_desc *csi_find_best_skip(struct v4l2_fract *in,
						      struct v4l2_fract *out)
{
	const struct csi_skip_desc *skip = &csi_skip[0], *best_skip = skip;
	u32 min_err = UINT_MAX;
	u64 want_us;
	int i;

	/* Default to 1:1 ratio */
	if (out->numerator == 0 || out->denominator == 0 ||
	    in->numerator == 0 || in->denominator == 0) {
		*out = *in;
		return best_skip;
	}

	want_us = div_u64((u64)USEC_PER_SEC * out->numerator, out->denominator);

	/* Find the reduction closest to the requested time per frame */
	for (i = 0; i < ARRAY_SIZE(csi_skip); i++, skip++) {
		u64 tmp, err;

		tmp = div_u64((u64)USEC_PER_SEC * in->numerator *
			      skip->max_ratio, in->denominator * skip->keep);

		err = abs((s64)tmp - want_us);
		if (err < min_err) {
			min_err = err;
			best_skip = skip;
		}
	}

	*out = *in;
	csi_apply_skip_interval(best_skip, out);

	return best_skip;
}