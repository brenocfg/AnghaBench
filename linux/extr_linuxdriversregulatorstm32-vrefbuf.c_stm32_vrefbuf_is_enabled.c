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
struct stm32_vrefbuf {scalar_t__ base; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int STM32_ENVR ; 
 scalar_t__ STM32_VREFBUF_CSR ; 
 struct stm32_vrefbuf* rdev_get_drvdata (struct regulator_dev*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int stm32_vrefbuf_is_enabled(struct regulator_dev *rdev)
{
	struct stm32_vrefbuf *priv = rdev_get_drvdata(rdev);

	return readl_relaxed(priv->base + STM32_VREFBUF_CSR) & STM32_ENVR;
}