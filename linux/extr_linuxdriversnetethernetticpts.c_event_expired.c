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
struct cpts_event {int /*<<< orphan*/  tmo; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_expired(struct cpts_event *event)
{
	return time_after(jiffies, event->tmo);
}