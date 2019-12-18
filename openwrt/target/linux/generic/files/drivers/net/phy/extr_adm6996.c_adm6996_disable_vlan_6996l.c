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
struct adm6996_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM_MAC_CLONE ; 
 int ADM_NUM_VLANS ; 
 int /*<<< orphan*/  ADM_SYSC3 ; 
 int /*<<< orphan*/  ADM_TBV ; 
 int /*<<< orphan*/  ADM_VLAN_MAP (int) ; 
 int /*<<< orphan*/  r16 (struct adm6996_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w16 (struct adm6996_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
adm6996_disable_vlan_6996l(struct adm6996_priv *priv)
{
	u16 reg;
	int i;

	for (i = 0; i < ADM_NUM_VLANS; i++) {
		w16(priv, ADM_VLAN_MAP(i), 0);
	}

	reg = r16(priv, ADM_SYSC3);
	reg &= ~(ADM_TBV);
	reg &= ~(ADM_MAC_CLONE);
	w16(priv, ADM_SYSC3, reg);
}