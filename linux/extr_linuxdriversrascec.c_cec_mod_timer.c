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

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (unsigned long) ; 

__attribute__((used)) static void cec_mod_timer(struct timer_list *t, unsigned long interval)
{
	unsigned long iv;

	iv = interval * HZ + jiffies;

	mod_timer(t, round_jiffies(iv));
}