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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int dummy; } ;
struct omap_dmic {int /*<<< orphan*/  mutex; scalar_t__ active; int /*<<< orphan*/  pm_qos_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 struct omap_dmic* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void omap_dmic_dai_shutdown(struct snd_pcm_substream *substream,
				    struct snd_soc_dai *dai)
{
	struct omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	mutex_lock(&dmic->mutex);

	pm_qos_remove_request(&dmic->pm_qos_req);

	if (!dai->active)
		dmic->active = 0;

	mutex_unlock(&dmic->mutex);
}