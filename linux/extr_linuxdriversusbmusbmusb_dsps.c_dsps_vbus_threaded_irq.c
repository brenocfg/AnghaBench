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
struct musb {int dummy; } ;
struct dsps_glue {int /*<<< orphan*/  dev; int /*<<< orphan*/  musb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsps_mod_timer (struct dsps_glue*,int /*<<< orphan*/ ) ; 
 struct musb* platform_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dsps_vbus_threaded_irq(int irq, void *priv)
{
	struct dsps_glue *glue = priv;
	struct musb *musb = platform_get_drvdata(glue->musb);

	if (!musb)
		return IRQ_NONE;

	dev_dbg(glue->dev, "VBUS interrupt\n");
	dsps_mod_timer(glue, 0);

	return IRQ_HANDLED;
}