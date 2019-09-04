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
struct wcove_typec {int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBC_CONTROL1 ; 
 int /*<<< orphan*/  USBC_IRQMASK1 ; 
 int /*<<< orphan*/  USBC_IRQMASK2 ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wcove_typec* tcpc_to_wcove (struct tcpc_dev*) ; 

__attribute__((used)) static int wcove_init(struct tcpc_dev *tcpc)
{
	struct wcove_typec *wcove = tcpc_to_wcove(tcpc);
	int ret;

	ret = regmap_write(wcove->regmap, USBC_CONTROL1, 0);
	if (ret)
		return ret;

	/* Unmask everything */
	ret = regmap_write(wcove->regmap, USBC_IRQMASK1, 0);
	if (ret)
		return ret;

	return regmap_write(wcove->regmap, USBC_IRQMASK2, 0);
}