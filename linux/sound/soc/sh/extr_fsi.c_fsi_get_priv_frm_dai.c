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
struct snd_soc_dai {scalar_t__ id; } ;
struct fsi_priv {int dummy; } ;
struct fsi_master {struct fsi_priv fsib; struct fsi_priv fsia; } ;

/* Variables and functions */
 struct fsi_master* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static struct fsi_priv *fsi_get_priv_frm_dai(struct snd_soc_dai *dai)
{
	struct fsi_master *master = snd_soc_dai_get_drvdata(dai);

	if (dai->id == 0)
		return &master->fsia;
	else
		return &master->fsib;
}