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
struct zd_rf {int type; int (* init_hw ) (struct zd_rf*) ;} ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
#define  AL2230S_RF 133 
#define  AL2230_RF 132 
#define  AL7230B_RF 131 
 int ENODEV ; 
#define  MAXIM_NEW_RF 130 
#define  RF2959_RF 129 
#define  UW2453_RF 128 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct zd_rf*) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_chip_lock_phy_regs (struct zd_chip*) ; 
 int zd_chip_unlock_phy_regs (struct zd_chip*) ; 
 int zd_rf_init_al2230 (struct zd_rf*) ; 
 int zd_rf_init_al7230b (struct zd_rf*) ; 
 int zd_rf_init_rf2959 (struct zd_rf*) ; 
 int zd_rf_init_uw2453 (struct zd_rf*) ; 
 int /*<<< orphan*/  zd_rf_name (int) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 

int zd_rf_init_hw(struct zd_rf *rf, u8 type)
{
	int r = 0;
	int t;
	struct zd_chip *chip = zd_rf_to_chip(rf);

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	switch (type) {
	case RF2959_RF:
		r = zd_rf_init_rf2959(rf);
		break;
	case AL2230_RF:
	case AL2230S_RF:
		r = zd_rf_init_al2230(rf);
		break;
	case AL7230B_RF:
		r = zd_rf_init_al7230b(rf);
		break;
	case MAXIM_NEW_RF:
	case UW2453_RF:
		r = zd_rf_init_uw2453(rf);
		break;
	default:
		dev_err(zd_chip_dev(chip),
			"RF %s %#x is not supported\n", zd_rf_name(type), type);
		rf->type = 0;
		return -ENODEV;
	}

	if (r)
		return r;

	rf->type = type;

	r = zd_chip_lock_phy_regs(chip);
	if (r)
		return r;
	t = rf->init_hw(rf);
	r = zd_chip_unlock_phy_regs(chip);
	if (t)
		r = t;
	return r;
}