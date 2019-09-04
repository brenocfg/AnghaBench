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
typedef  int /*<<< orphan*/  u8 ;
struct aat2870_data {int (* write ) (struct aat2870_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct aat2870_bl_driver_data {scalar_t__ channels; TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAT2870_BL_CH_EN ; 
 struct aat2870_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int stub1 (struct aat2870_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int aat2870_bl_enable(struct aat2870_bl_driver_data *aat2870_bl)
{
	struct aat2870_data *aat2870
			= dev_get_drvdata(aat2870_bl->pdev->dev.parent);

	return aat2870->write(aat2870, AAT2870_BL_CH_EN,
			      (u8)aat2870_bl->channels);
}