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
struct vx_core {int dummy; } ;

/* Variables and functions */
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxp_reg_addr (struct vx_core*,int) ; 

__attribute__((used)) static unsigned char vxp_inb(struct vx_core *chip, int offset)
{
	return inb(vxp_reg_addr(chip, offset));
}