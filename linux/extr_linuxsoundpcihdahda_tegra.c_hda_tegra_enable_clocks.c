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
struct hda_tegra {int /*<<< orphan*/  hda_clk; int /*<<< orphan*/  hda2codec_2x_clk; int /*<<< orphan*/  hda2hdmi_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hda_tegra_enable_clocks(struct hda_tegra *data)
{
	int rc;

	rc = clk_prepare_enable(data->hda_clk);
	if (rc)
		return rc;
	rc = clk_prepare_enable(data->hda2codec_2x_clk);
	if (rc)
		goto disable_hda;
	rc = clk_prepare_enable(data->hda2hdmi_clk);
	if (rc)
		goto disable_codec_2x;

	return 0;

disable_codec_2x:
	clk_disable_unprepare(data->hda2codec_2x_clk);
disable_hda:
	clk_disable_unprepare(data->hda_clk);
	return rc;
}