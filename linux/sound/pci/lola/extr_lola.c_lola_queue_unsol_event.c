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
struct lola {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lola_update_ext_clock_freq (struct lola*,unsigned int) ; 

__attribute__((used)) static void lola_queue_unsol_event(struct lola *chip, unsigned int res,
				   unsigned int res_ex)
{
	lola_update_ext_clock_freq(chip, res);
}