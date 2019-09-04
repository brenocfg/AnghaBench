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
struct brcms_info {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static inline int brcms_led_register(struct brcms_info *wl)
{
	return -ENOTSUPP;
}