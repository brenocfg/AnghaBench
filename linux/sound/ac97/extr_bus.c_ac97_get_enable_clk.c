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
struct ac97_codec_device {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ac97_get_enable_clk(struct ac97_codec_device *adev)
{
	int ret;

	adev->clk = clk_get(&adev->dev, "ac97_clk");
	if (IS_ERR(adev->clk))
		return PTR_ERR(adev->clk);

	ret = clk_prepare_enable(adev->clk);
	if (ret)
		clk_put(adev->clk);

	return ret;
}