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
struct asus_laptop {int dummy; } ;

/* Variables and functions */
 int asus_gps_switch (struct asus_laptop*,int) ; 

__attribute__((used)) static int asus_gps_rfkill_set(void *data, bool blocked)
{
	struct asus_laptop *asus = data;

	return asus_gps_switch(asus, !blocked);
}