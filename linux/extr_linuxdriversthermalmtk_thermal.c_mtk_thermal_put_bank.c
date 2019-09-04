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
struct mtk_thermal_bank {struct mtk_thermal* mt; } ;
struct mtk_thermal {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_thermal_put_bank(struct mtk_thermal_bank *bank)
{
	struct mtk_thermal *mt = bank->mt;

	mutex_unlock(&mt->lock);
}