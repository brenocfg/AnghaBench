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
typedef  int /*<<< orphan*/  u16 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCP_EEE_AR ; 
 int /*<<< orphan*/  OCP_EEE_DATA ; 
 int /*<<< orphan*/  ocp_reg_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_reg_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8152_mmd_indirect (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 r8152_mmd_read(struct r8152 *tp, u16 dev, u16 reg)
{
	u16 data;

	r8152_mmd_indirect(tp, dev, reg);
	data = ocp_reg_read(tp, OCP_EEE_DATA);
	ocp_reg_write(tp, OCP_EEE_AR, 0x0000);

	return data;
}