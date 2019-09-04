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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct m48t59_private {int /*<<< orphan*/  lock; } ;
struct m48t59_plat_data {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  M48T59_READ (size_t) ; 
 struct m48t59_plat_data* dev_get_platdata (struct device*) ; 
 struct m48t59_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int m48t59_nvram_read(void *priv, unsigned int offset, void *val,
			     size_t size)
{
	struct platform_device *pdev = priv;
	struct device *dev = &pdev->dev;
	struct m48t59_plat_data *pdata = dev_get_platdata(&pdev->dev);
	struct m48t59_private *m48t59 = platform_get_drvdata(pdev);
	ssize_t cnt = 0;
	unsigned long flags;
	u8 *buf = val;

	spin_lock_irqsave(&m48t59->lock, flags);

	for (; cnt < size; cnt++)
		*buf++ = M48T59_READ(cnt);

	spin_unlock_irqrestore(&m48t59->lock, flags);

	return 0;
}