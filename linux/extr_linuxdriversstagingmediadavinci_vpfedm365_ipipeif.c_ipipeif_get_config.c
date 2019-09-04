#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  n; int /*<<< orphan*/  m; } ;
struct TYPE_13__ {int /*<<< orphan*/  thr; int /*<<< orphan*/  en; } ;
struct TYPE_17__ {TYPE_7__ clk_div; TYPE_4__ dpc; int /*<<< orphan*/  clip; int /*<<< orphan*/  align_sync; int /*<<< orphan*/  rsz_start; int /*<<< orphan*/  df_gain_en; int /*<<< orphan*/  df_gain; int /*<<< orphan*/  df_gain_thr; } ;
struct TYPE_18__ {TYPE_8__ if_5_1; int /*<<< orphan*/  avg_filter; int /*<<< orphan*/  decimation; int /*<<< orphan*/  rsz; int /*<<< orphan*/  lpfr; int /*<<< orphan*/  ppln; int /*<<< orphan*/  clock_select; } ;
struct TYPE_11__ {TYPE_1__* v4l2_dev; } ;
struct vpfe_ipipeif_device {TYPE_9__ config; TYPE_2__ subdev; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  n; int /*<<< orphan*/  m; } ;
struct TYPE_12__ {int /*<<< orphan*/  thr; int /*<<< orphan*/  en; } ;
struct TYPE_15__ {TYPE_5__ clk_div; TYPE_3__ dpc; int /*<<< orphan*/  clip; int /*<<< orphan*/  align_sync; int /*<<< orphan*/  rsz_start; int /*<<< orphan*/  df_gain_en; int /*<<< orphan*/  df_gain; int /*<<< orphan*/  df_gain_thr; } ;
struct ipipeif_params {TYPE_6__ if_5_1; int /*<<< orphan*/  avg_filter; int /*<<< orphan*/  decimation; int /*<<< orphan*/  rsz; int /*<<< orphan*/  lpfr; int /*<<< orphan*/  ppln; int /*<<< orphan*/  clock_select; } ;
struct device {int dummy; } ;
struct TYPE_10__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct vpfe_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
ipipeif_get_config(struct v4l2_subdev *sd, void *arg)
{
	struct vpfe_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct ipipeif_params *config = arg;
	struct device *dev = ipipeif->subdev.v4l2_dev->dev;

	if (!arg) {
		dev_err(dev, "Invalid configuration pointer\n");
		return -EINVAL;
	}

	config->clock_select = ipipeif->config.clock_select;
	config->ppln = ipipeif->config.ppln;
	config->lpfr = ipipeif->config.lpfr;
	config->rsz = ipipeif->config.rsz;
	config->decimation = ipipeif->config.decimation;
	config->avg_filter = ipipeif->config.avg_filter;

	config->if_5_1.df_gain_thr = ipipeif->config.if_5_1.df_gain_thr;
	config->if_5_1.df_gain = ipipeif->config.if_5_1.df_gain;
	config->if_5_1.df_gain_en = ipipeif->config.if_5_1.df_gain_en;

	config->if_5_1.rsz_start = ipipeif->config.if_5_1.rsz_start;
	config->if_5_1.align_sync = ipipeif->config.if_5_1.align_sync;
	config->if_5_1.clip = ipipeif->config.if_5_1.clip;

	config->if_5_1.dpc.en = ipipeif->config.if_5_1.dpc.en;
	config->if_5_1.dpc.thr = ipipeif->config.if_5_1.dpc.thr;

	config->if_5_1.clk_div.m = ipipeif->config.if_5_1.clk_div.m;
	config->if_5_1.clk_div.n = ipipeif->config.if_5_1.clk_div.n;

	return 0;
}