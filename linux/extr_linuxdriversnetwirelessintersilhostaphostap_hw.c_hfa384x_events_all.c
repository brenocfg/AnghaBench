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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_EVENT_MASK ; 
 int /*<<< orphan*/  HFA384X_INTEN_OFF ; 
 int /*<<< orphan*/  HFA384X_OUTW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfa384x_events_all(struct net_device *dev)
{
	HFA384X_OUTW(HFA384X_EVENT_MASK, HFA384X_INTEN_OFF);
}