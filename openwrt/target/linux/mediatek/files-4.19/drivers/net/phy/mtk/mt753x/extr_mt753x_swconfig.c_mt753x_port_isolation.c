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
struct gsw_mt753x {int cpu_port; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MT753X_NUM_PORTS ; 
 int /*<<< orphan*/  PCR (int) ; 
 int PORT_MATRIX_M ; 
 int PORT_MATRIX_S ; 
 int /*<<< orphan*/  PVC (int) ; 
 int STAG_VPID_S ; 
 int VA_TRANSPARENT_PORT ; 
 int VLAN_ATTR_S ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt753x_port_isolation(struct gsw_mt753x *gsw)
{
	int i;

	for (i = 0; i < MT753X_NUM_PORTS; i++)
		mt753x_reg_write(gsw, PCR(i),
				 BIT(gsw->cpu_port) << PORT_MATRIX_S);

	mt753x_reg_write(gsw, PCR(gsw->cpu_port), PORT_MATRIX_M);

	for (i = 0; i < MT753X_NUM_PORTS; i++)
		mt753x_reg_write(gsw, PVC(i),
				 (0x8100 << STAG_VPID_S) |
				 (VA_TRANSPARENT_PORT << VLAN_ATTR_S));
}