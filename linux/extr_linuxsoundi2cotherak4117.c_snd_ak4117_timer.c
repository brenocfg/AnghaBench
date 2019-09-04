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
struct timer_list {int dummy; } ;
struct ak4117 {int /*<<< orphan*/  timer; scalar_t__ init; } ;

/* Variables and functions */
 struct ak4117* chip ; 
 struct ak4117* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_ak4117_check_rate_and_errors (struct ak4117*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void snd_ak4117_timer(struct timer_list *t)
{
	struct ak4117 *chip = from_timer(chip, t, timer);

	if (chip->init)
		return;
	snd_ak4117_check_rate_and_errors(chip, 0);
	mod_timer(&chip->timer, 1 + jiffies);
}