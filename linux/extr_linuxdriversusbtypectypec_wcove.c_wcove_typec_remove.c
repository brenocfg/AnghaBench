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
struct wcove_typec {int /*<<< orphan*/  tcpm; int /*<<< orphan*/  regmap; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBC_IRQMASK1 ; 
 unsigned int USBC_IRQMASK1_ALL ; 
 int /*<<< orphan*/  USBC_IRQMASK2 ; 
 unsigned int USBC_IRQMASK2_ALL ; 
 struct wcove_typec* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tcpm_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcove_typec_remove(struct platform_device *pdev)
{
	struct wcove_typec *wcove = platform_get_drvdata(pdev);
	unsigned int val;

	/* Mask everything */
	regmap_read(wcove->regmap, USBC_IRQMASK1, &val);
	regmap_write(wcove->regmap, USBC_IRQMASK1, val | USBC_IRQMASK1_ALL);
	regmap_read(wcove->regmap, USBC_IRQMASK2, &val);
	regmap_write(wcove->regmap, USBC_IRQMASK2, val | USBC_IRQMASK2_ALL);

	tcpm_unregister_port(wcove->tcpm);

	return 0;
}