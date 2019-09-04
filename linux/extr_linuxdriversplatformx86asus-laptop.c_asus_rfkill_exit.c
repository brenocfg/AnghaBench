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
struct asus_laptop {int /*<<< orphan*/  gps; int /*<<< orphan*/  wlan; int /*<<< orphan*/  bluetooth; int /*<<< orphan*/  wwan; } ;

/* Variables and functions */
 int /*<<< orphan*/  asus_rfkill_terminate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asus_rfkill_exit(struct asus_laptop *asus)
{
	asus_rfkill_terminate(&asus->wwan);
	asus_rfkill_terminate(&asus->bluetooth);
	asus_rfkill_terminate(&asus->wlan);
	asus_rfkill_terminate(&asus->gps);
}