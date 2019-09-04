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
typedef  int u8 ;
struct phy_dm_struct {int /*<<< orphan*/  adaptivity; int /*<<< orphan*/  dm_cfo_track; int /*<<< orphan*/  false_alm_cnt; } ;

/* Variables and functions */
#define  PHYDM_ADAPTIVITY 130 
#define  PHYDM_CFOTRACK 129 
#define  PHYDM_FALSEALMCNT 128 

void *phydm_get_structure(struct phy_dm_struct *dm, u8 structure_type)

{
	void *p_struct = NULL;

	switch (structure_type) {
	case PHYDM_FALSEALMCNT:
		p_struct = &dm->false_alm_cnt;
		break;

	case PHYDM_CFOTRACK:
		p_struct = &dm->dm_cfo_track;
		break;

	case PHYDM_ADAPTIVITY:
		p_struct = &dm->adaptivity;
		break;

	default:
		break;
	}

	return p_struct;
}