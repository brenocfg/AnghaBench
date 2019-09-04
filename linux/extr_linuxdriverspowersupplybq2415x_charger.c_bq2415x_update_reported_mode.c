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
struct bq2415x_device {int reported_mode; } ;
typedef  enum bq2415x_mode { ____Placeholder_bq2415x_mode } bq2415x_mode ;

/* Variables and functions */
 int BQ2415X_MODE_DEDICATED_CHARGER ; 
 int BQ2415X_MODE_HOST_CHARGER ; 
 int BQ2415X_MODE_NONE ; 
 int BQ2415X_MODE_OFF ; 

__attribute__((used)) static bool bq2415x_update_reported_mode(struct bq2415x_device *bq, int mA)
{
	enum bq2415x_mode mode;

	if (mA == 0)
		mode = BQ2415X_MODE_OFF;
	else if (mA < 500)
		mode = BQ2415X_MODE_NONE;
	else if (mA < 1800)
		mode = BQ2415X_MODE_HOST_CHARGER;
	else
		mode = BQ2415X_MODE_DEDICATED_CHARGER;

	if (bq->reported_mode == mode)
		return false;

	bq->reported_mode = mode;
	return true;
}