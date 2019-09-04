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
struct bfad_s {int /*<<< orphan*/  hal_tmo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TIMER_FREQ ; 
 int /*<<< orphan*/  bfad_bfa_tmo ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfad_init_timer(struct bfad_s *bfad)
{
	timer_setup(&bfad->hal_tmo, bfad_bfa_tmo, 0);

	mod_timer(&bfad->hal_tmo,
		  jiffies + msecs_to_jiffies(BFA_TIMER_FREQ));
}