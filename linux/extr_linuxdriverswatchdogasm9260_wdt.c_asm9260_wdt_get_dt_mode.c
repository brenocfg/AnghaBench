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
struct asm9260_wdt_priv {TYPE_1__* dev; void* mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 void* DEBUG ; 
 void* HW_RESET ; 
 void* SW_RESET ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,char const*) ; 
 int of_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void asm9260_wdt_get_dt_mode(struct asm9260_wdt_priv *priv)
{
	const char *tmp;
	int ret;

	/* default mode */
	priv->mode = HW_RESET;

	ret = of_property_read_string(priv->dev->of_node,
				      "alphascale,mode", &tmp);
	if (ret < 0)
		return;

	if (!strcmp(tmp, "hw"))
		priv->mode = HW_RESET;
	else if (!strcmp(tmp, "sw"))
		priv->mode = SW_RESET;
	else if (!strcmp(tmp, "debug"))
		priv->mode = DEBUG;
	else
		dev_warn(priv->dev, "unknown reset-type: %s. Using default \"hw\" mode.",
			 tmp);
}