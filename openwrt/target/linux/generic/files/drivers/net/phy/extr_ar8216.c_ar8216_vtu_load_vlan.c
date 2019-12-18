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
typedef  int u32 ;
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int AR8216_VTU_OP_LOAD ; 
 int AR8216_VTU_VID_S ; 
 int /*<<< orphan*/  ar8216_vtu_op (struct ar8xxx_priv*,int,int) ; 

__attribute__((used)) static void
ar8216_vtu_load_vlan(struct ar8xxx_priv *priv, u32 vid, u32 port_mask)
{
	u32 op;

	op = AR8216_VTU_OP_LOAD | (vid << AR8216_VTU_VID_S);
	ar8216_vtu_op(priv, op, port_mask);
}