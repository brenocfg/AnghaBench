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
struct word_at_a_time {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long prep_zero_mask(unsigned long a, unsigned long bits, const struct word_at_a_time *c)
{
	return bits;
}