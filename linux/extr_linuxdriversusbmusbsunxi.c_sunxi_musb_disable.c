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
struct sunxi_glue {int /*<<< orphan*/  flags; } ;
struct musb {TYPE_1__* controller; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUNXI_MUSB_FL_ENABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sunxi_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunxi_musb_disable(struct musb *musb)
{
	struct sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	clear_bit(SUNXI_MUSB_FL_ENABLED, &glue->flags);
}