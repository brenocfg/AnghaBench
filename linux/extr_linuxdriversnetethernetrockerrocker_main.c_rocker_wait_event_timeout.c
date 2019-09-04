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
struct rocker_wait {int /*<<< orphan*/  done; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool rocker_wait_event_timeout(struct rocker_wait *wait,
				      unsigned long timeout)
{
	wait_event_timeout(wait->wait, wait->done, HZ / 10);
	if (!wait->done)
		return false;
	return true;
}