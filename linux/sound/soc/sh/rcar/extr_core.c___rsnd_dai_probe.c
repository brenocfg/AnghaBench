#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int channels_min; int channels_max; int /*<<< orphan*/  stream_name; void* formats; void* rates; } ;
struct TYPE_3__ {int channels_min; int channels_max; int /*<<< orphan*/  stream_name; void* formats; void* rates; } ;
struct snd_soc_dai_driver {int symmetric_rates; TYPE_2__ capture; TYPE_1__ playback; int /*<<< orphan*/  pcm_new; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_dai_stream {struct rsnd_dai* rdai; int /*<<< orphan*/  name; } ;
struct rsnd_dai {int /*<<< orphan*/  name; struct rsnd_priv* priv; struct rsnd_dai_stream capture; struct rsnd_dai_stream playback; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSND_DAI_NAME_SIZE ; 
 void* RSND_FMTS ; 
 void* RSND_RATES ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 struct snd_soc_dai_driver* rsnd_daidrv_get (struct rsnd_priv*,int) ; 
 scalar_t__ rsnd_io_to_mod_ssi (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_parse_connect_ctu (struct rsnd_dai*,struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  rsnd_parse_connect_dvc (struct rsnd_dai*,struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  rsnd_parse_connect_mix (struct rsnd_dai*,struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  rsnd_parse_connect_src (struct rsnd_dai*,struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  rsnd_parse_connect_ssi (struct rsnd_dai*,struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  rsnd_parse_connect_ssiu (struct rsnd_dai*,struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  rsnd_pcm_new ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_rdai_channels_set (struct rsnd_dai*,int) ; 
 struct rsnd_dai* rsnd_rdai_get (struct rsnd_priv*,int) ; 
 int /*<<< orphan*/  rsnd_rdai_ssi_lane_set (struct rsnd_dai*,int) ; 
 int /*<<< orphan*/  rsnd_rdai_width_set (struct rsnd_dai*,int) ; 
 int /*<<< orphan*/  rsnd_soc_dai_ops ; 
 scalar_t__ rsnd_ssi_is_pin_sharing (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void __rsnd_dai_probe(struct rsnd_priv *priv,
			     struct device_node *dai_np,
			     int dai_i)
{
	struct device_node *playback, *capture;
	struct rsnd_dai_stream *io_playback;
	struct rsnd_dai_stream *io_capture;
	struct snd_soc_dai_driver *drv;
	struct rsnd_dai *rdai;
	struct device *dev = rsnd_priv_to_dev(priv);
	int io_i;

	rdai		= rsnd_rdai_get(priv, dai_i);
	drv		= rsnd_daidrv_get(priv, dai_i);
	io_playback	= &rdai->playback;
	io_capture	= &rdai->capture;

	snprintf(rdai->name, RSND_DAI_NAME_SIZE, "rsnd-dai.%d", dai_i);

	rdai->priv	= priv;
	drv->name	= rdai->name;
	drv->ops	= &rsnd_soc_dai_ops;
	drv->pcm_new	= rsnd_pcm_new;

	snprintf(io_playback->name, RSND_DAI_NAME_SIZE,
		 "DAI%d Playback", dai_i);
	drv->playback.rates		= RSND_RATES;
	drv->playback.formats		= RSND_FMTS;
	drv->playback.channels_min	= 2;
	drv->playback.channels_max	= 8;
	drv->playback.stream_name	= io_playback->name;

	snprintf(io_capture->name, RSND_DAI_NAME_SIZE,
		 "DAI%d Capture", dai_i);
	drv->capture.rates		= RSND_RATES;
	drv->capture.formats		= RSND_FMTS;
	drv->capture.channels_min	= 2;
	drv->capture.channels_max	= 8;
	drv->capture.stream_name	= io_capture->name;

	io_playback->rdai		= rdai;
	io_capture->rdai		= rdai;
	rsnd_rdai_channels_set(rdai, 2); /* default 2ch */
	rsnd_rdai_ssi_lane_set(rdai, 1); /* default 1lane */
	rsnd_rdai_width_set(rdai, 32);   /* default 32bit width */

	for (io_i = 0;; io_i++) {
		playback = of_parse_phandle(dai_np, "playback", io_i);
		capture  = of_parse_phandle(dai_np, "capture", io_i);

		if (!playback && !capture)
			break;

		rsnd_parse_connect_ssi(rdai, playback, capture);
		rsnd_parse_connect_ssiu(rdai, playback, capture);
		rsnd_parse_connect_src(rdai, playback, capture);
		rsnd_parse_connect_ctu(rdai, playback, capture);
		rsnd_parse_connect_mix(rdai, playback, capture);
		rsnd_parse_connect_dvc(rdai, playback, capture);

		of_node_put(playback);
		of_node_put(capture);
	}

	if (rsnd_ssi_is_pin_sharing(io_capture) ||
	    rsnd_ssi_is_pin_sharing(io_playback)) {
		/* should have symmetric_rates if pin sharing */
		drv->symmetric_rates = 1;
	}

	dev_dbg(dev, "%s (%s/%s)\n", rdai->name,
		rsnd_io_to_mod_ssi(io_playback) ? "play"    : " -- ",
		rsnd_io_to_mod_ssi(io_capture) ? "capture" : "  --   ");
}