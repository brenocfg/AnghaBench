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

/* Variables and functions */
 int /*<<< orphan*/  ISAPNP_CFG_ACTIVATE ; 
 int /*<<< orphan*/  isapnp_device (unsigned char) ; 
 int /*<<< orphan*/  isapnp_write_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void isapnp_activate(unsigned char logdev)
{
	isapnp_device(logdev);
	isapnp_write_byte(ISAPNP_CFG_ACTIVATE, 1);
	udelay(250);
}