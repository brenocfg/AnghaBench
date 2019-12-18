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
struct sspa_priv {int /*<<< orphan*/  sysclk; int /*<<< orphan*/  audio_clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct sspa_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int asoc_mmp_sspa_remove(struct platform_device *pdev)
{
	struct sspa_priv *priv = platform_get_drvdata(pdev);

	clk_disable(priv->audio_clk);
	clk_put(priv->audio_clk);
	clk_put(priv->sysclk);
	return 0;
}