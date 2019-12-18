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
struct cache_detail {scalar_t__ last_close; int /*<<< orphan*/  writers; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int seconds_since_boot () ; 

__attribute__((used)) static bool cache_listeners_exist(struct cache_detail *detail)
{
	if (atomic_read(&detail->writers))
		return true;
	if (detail->last_close == 0)
		/* This cache was never opened */
		return false;
	if (detail->last_close < seconds_since_boot() - 30)
		/*
		 * We allow for the possibility that someone might
		 * restart a userspace daemon without restarting the
		 * server; but after 30 seconds, we give up.
		 */
		 return false;
	return true;
}