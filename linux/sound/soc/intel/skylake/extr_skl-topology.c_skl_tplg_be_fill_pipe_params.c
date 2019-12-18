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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct skl_pipe_params {int s_freq; int /*<<< orphan*/  s_fmt; int /*<<< orphan*/  ch; int /*<<< orphan*/  stream; } ;
struct TYPE_2__ {int /*<<< orphan*/ * caps; int /*<<< orphan*/  caps_size; } ;
struct skl_module_cfg {int /*<<< orphan*/  vbus_id; TYPE_1__ formats_config; int /*<<< orphan*/  dev_type; } ;
struct skl_dev {int dummy; } ;
struct nhlt_specific_cfg {int /*<<< orphan*/  caps; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 int NHLT_LINK_HDA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct skl_dev* get_skl_ctx (int /*<<< orphan*/ ) ; 
 struct nhlt_specific_cfg* skl_get_ep_blob (struct skl_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_tplg_be_dev_type (int /*<<< orphan*/ ) ; 
 int skl_tplg_be_link_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_tplg_fill_dma_id (struct skl_module_cfg*,struct skl_pipe_params*) ; 

__attribute__((used)) static int skl_tplg_be_fill_pipe_params(struct snd_soc_dai *dai,
				struct skl_module_cfg *mconfig,
				struct skl_pipe_params *params)
{
	struct nhlt_specific_cfg *cfg;
	struct skl_dev *skl = get_skl_ctx(dai->dev);
	int link_type = skl_tplg_be_link_type(mconfig->dev_type);
	u8 dev_type = skl_tplg_be_dev_type(mconfig->dev_type);

	skl_tplg_fill_dma_id(mconfig, params);

	if (link_type == NHLT_LINK_HDA)
		return 0;

	/* update the blob based on virtual bus_id*/
	cfg = skl_get_ep_blob(skl, mconfig->vbus_id, link_type,
					params->s_fmt, params->ch,
					params->s_freq, params->stream,
					dev_type);
	if (cfg) {
		mconfig->formats_config.caps_size = cfg->size;
		mconfig->formats_config.caps = (u32 *) &cfg->caps;
	} else {
		dev_err(dai->dev, "Blob NULL for id %x type %d dirn %d\n",
					mconfig->vbus_id, link_type,
					params->stream);
		dev_err(dai->dev, "PCM: ch %d, freq %d, fmt %d\n",
				 params->ch, params->s_freq, params->s_fmt);
		return -EINVAL;
	}

	return 0;
}