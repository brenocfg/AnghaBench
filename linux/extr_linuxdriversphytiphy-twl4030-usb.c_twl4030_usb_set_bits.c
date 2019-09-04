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
struct twl4030_usb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULPI_SET (int /*<<< orphan*/ ) ; 
 int twl4030_usb_write (struct twl4030_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
twl4030_usb_set_bits(struct twl4030_usb *twl, u8 reg, u8 bits)
{
	return twl4030_usb_write(twl, ULPI_SET(reg), bits);
}