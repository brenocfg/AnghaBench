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
typedef  scalar_t__ u32 ;
struct renesas_usb3 {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void usb3_write(struct renesas_usb3 *usb3, u32 data, u32 offs)
{
	iowrite32(data, usb3->reg + offs);
}