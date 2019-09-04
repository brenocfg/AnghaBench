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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct slim_device {int dummy; } ;

/* Variables and functions */
 int slim_write (struct slim_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int slim_writeb(struct slim_device *sdev, u32 addr, u8 value)
{
	return slim_write(sdev, addr, 1, &value);
}