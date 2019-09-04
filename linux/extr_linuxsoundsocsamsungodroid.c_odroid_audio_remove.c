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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_of_node; } ;
struct odroid_priv {int /*<<< orphan*/  clk_i2s_bus; int /*<<< orphan*/  sclk_i2s; TYPE_1__ dai_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct odroid_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_of_put_dai_link_codecs (TYPE_1__*) ; 

__attribute__((used)) static int odroid_audio_remove(struct platform_device *pdev)
{
	struct odroid_priv *priv = platform_get_drvdata(pdev);

	of_node_put(priv->dai_link.cpu_of_node);
	snd_soc_of_put_dai_link_codecs(&priv->dai_link);
	clk_put(priv->sclk_i2s);
	clk_put(priv->clk_i2s_bus);

	return 0;
}