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
struct tick_device {int dummy; } ;

/* Variables and functions */
 struct tick_device tick_broadcast_device ; 

struct tick_device *tick_get_broadcast_device(void)
{
	return &tick_broadcast_device;
}