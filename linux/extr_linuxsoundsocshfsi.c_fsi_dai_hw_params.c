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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsi_clk_valid (struct fsi_priv*,int /*<<< orphan*/ ) ; 
 struct fsi_priv* fsi_get_priv (struct snd_pcm_substream*) ; 
 scalar_t__ fsi_is_clk_master (struct fsi_priv*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int fsi_dai_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct fsi_priv *fsi = fsi_get_priv(substream);

	if (fsi_is_clk_master(fsi))
		fsi_clk_valid(fsi, params_rate(params));

	return 0;
}