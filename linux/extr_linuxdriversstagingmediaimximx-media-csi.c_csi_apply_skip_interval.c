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
struct v4l2_fract {unsigned int numerator; unsigned int denominator; } ;
struct csi_skip_desc {unsigned int max_ratio; unsigned int keep; } ;

/* Variables and functions */
 unsigned int gcd (unsigned int,unsigned int) ; 

__attribute__((used)) static void csi_apply_skip_interval(const struct csi_skip_desc *skip,
				    struct v4l2_fract *interval)
{
	unsigned int div;

	interval->numerator *= skip->max_ratio;
	interval->denominator *= skip->keep;

	/* Reduce fraction to lowest terms */
	div = gcd(interval->numerator, interval->denominator);
	if (div > 1) {
		interval->numerator /= div;
		interval->denominator /= div;
	}
}