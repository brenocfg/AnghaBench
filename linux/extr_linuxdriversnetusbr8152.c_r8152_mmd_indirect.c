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
typedef  int u16 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int FUN_ADDR ; 
 int FUN_DATA ; 
 int /*<<< orphan*/  OCP_EEE_AR ; 
 int /*<<< orphan*/  OCP_EEE_DATA ; 
 int /*<<< orphan*/  ocp_reg_write (struct r8152*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void r8152_mmd_indirect(struct r8152 *tp, u16 dev, u16 reg)
{
	ocp_reg_write(tp, OCP_EEE_AR, FUN_ADDR | dev);
	ocp_reg_write(tp, OCP_EEE_DATA, reg);
	ocp_reg_write(tp, OCP_EEE_AR, FUN_DATA | dev);
}