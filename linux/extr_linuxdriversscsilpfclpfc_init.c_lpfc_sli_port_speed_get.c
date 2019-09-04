#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int logical_speed; int speed; } ;
struct TYPE_4__ {TYPE_1__ link_state; } ;
struct lpfc_hba {scalar_t__ sli_rev; int fc_linkspeed; TYPE_2__ sli4_hba; } ;

/* Variables and functions */
#define  LPFC_LINK_SPEED_10GHZ 133 
#define  LPFC_LINK_SPEED_16GHZ 132 
#define  LPFC_LINK_SPEED_1GHZ 131 
#define  LPFC_LINK_SPEED_2GHZ 130 
#define  LPFC_LINK_SPEED_4GHZ 129 
#define  LPFC_LINK_SPEED_8GHZ 128 
 scalar_t__ LPFC_SLI_REV3 ; 
 int /*<<< orphan*/  lpfc_is_link_up (struct lpfc_hba*) ; 

uint32_t
lpfc_sli_port_speed_get(struct lpfc_hba *phba)
{
	uint32_t link_speed;

	if (!lpfc_is_link_up(phba))
		return 0;

	if (phba->sli_rev <= LPFC_SLI_REV3) {
		switch (phba->fc_linkspeed) {
		case LPFC_LINK_SPEED_1GHZ:
			link_speed = 1000;
			break;
		case LPFC_LINK_SPEED_2GHZ:
			link_speed = 2000;
			break;
		case LPFC_LINK_SPEED_4GHZ:
			link_speed = 4000;
			break;
		case LPFC_LINK_SPEED_8GHZ:
			link_speed = 8000;
			break;
		case LPFC_LINK_SPEED_10GHZ:
			link_speed = 10000;
			break;
		case LPFC_LINK_SPEED_16GHZ:
			link_speed = 16000;
			break;
		default:
			link_speed = 0;
		}
	} else {
		if (phba->sli4_hba.link_state.logical_speed)
			link_speed =
			      phba->sli4_hba.link_state.logical_speed;
		else
			link_speed = phba->sli4_hba.link_state.speed;
	}
	return link_speed;
}