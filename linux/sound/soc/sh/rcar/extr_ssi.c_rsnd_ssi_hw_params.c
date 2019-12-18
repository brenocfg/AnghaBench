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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {unsigned int chan_width; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 struct rsnd_priv* rsnd_io_to_priv (struct rsnd_dai_stream*) ; 
 struct rsnd_dai* rsnd_io_to_rdai (struct rsnd_dai_stream*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 unsigned int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsnd_ssi_hw_params(struct rsnd_mod *mod,
			      struct rsnd_dai_stream *io,
			      struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params)
{
	struct rsnd_dai *rdai = rsnd_io_to_rdai(io);
	unsigned int fmt_width = snd_pcm_format_width(params_format(params));

	if (fmt_width > rdai->chan_width) {
		struct rsnd_priv *priv = rsnd_io_to_priv(io);
		struct device *dev = rsnd_priv_to_dev(priv);

		dev_err(dev, "invalid combination of slot-width and format-data-width\n");
		return -EINVAL;
	}

	return 0;
}