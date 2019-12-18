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
struct atm_trafprm {int max_sdu; scalar_t__ max_cdv; int /*<<< orphan*/  traffic_class; } ;

/* Variables and functions */
#define  ATM_AAL0 130 
#define  ATM_AAL34 129 
#define  ATM_AAL5 128 
 int /*<<< orphan*/  ATM_CELL_SIZE ; 
 int ATM_MAX_AAL34_PDU ; 
 int ATM_MAX_AAL5_PDU ; 
 scalar_t__ ATM_MAX_CDV ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned char) ; 

__attribute__((used)) static int adjust_tp(struct atm_trafprm *tp, unsigned char aal)
{
	int max_sdu;

	if (!tp->traffic_class)
		return 0;
	switch (aal) {
	case ATM_AAL0:
		max_sdu = ATM_CELL_SIZE-1;
		break;
	case ATM_AAL34:
		max_sdu = ATM_MAX_AAL34_PDU;
		break;
	default:
		pr_warn("AAL problems ... (%d)\n", aal);
		/* fall through */
	case ATM_AAL5:
		max_sdu = ATM_MAX_AAL5_PDU;
	}
	if (!tp->max_sdu)
		tp->max_sdu = max_sdu;
	else if (tp->max_sdu > max_sdu)
		return -EINVAL;
	if (!tp->max_cdv)
		tp->max_cdv = ATM_MAX_CDV;
	return 0;
}