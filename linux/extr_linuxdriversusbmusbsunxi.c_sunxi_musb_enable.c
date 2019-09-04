#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sunxi_glue {int /*<<< orphan*/  work; int /*<<< orphan*/  flags; struct musb* musb; } ;
struct musb {TYPE_1__* controller; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUNXI_MUSB_FL_ENABLED ; 
 struct sunxi_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunxi_musb_enable(struct musb *musb)
{
	struct sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	glue->musb = musb;

	/* musb_core does not call us in a balanced manner */
	if (test_and_set_bit(SUNXI_MUSB_FL_ENABLED, &glue->flags))
		return;

	schedule_work(&glue->work);
}