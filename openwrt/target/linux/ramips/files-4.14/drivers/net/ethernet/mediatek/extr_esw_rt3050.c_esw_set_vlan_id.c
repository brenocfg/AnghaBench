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
struct rt305x_esw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT305X_ESW_REG_VLANI (unsigned int) ; 
 unsigned int RT305X_ESW_VLANI_VID_M ; 
 unsigned int RT305X_ESW_VLANI_VID_S ; 
 int /*<<< orphan*/  esw_rmw (struct rt305x_esw*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void esw_set_vlan_id(struct rt305x_esw *esw, unsigned vlan, unsigned vid)
{
	unsigned s;

	s = RT305X_ESW_VLANI_VID_S * (vlan % 2);
	esw_rmw(esw,
		       RT305X_ESW_REG_VLANI(vlan / 2),
		       RT305X_ESW_VLANI_VID_M << s,
		       (vid & RT305X_ESW_VLANI_VID_M) << s);
}