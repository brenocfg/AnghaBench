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
struct sst_ids {int dummy; } ;
struct sst_data {int /*<<< orphan*/  lock; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; struct sst_ids* priv; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sst_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_find_and_send_pipe_algo (struct sst_data*,int /*<<< orphan*/ ,struct sst_ids*) ; 
 int /*<<< orphan*/  sst_set_pipe_gain (struct sst_ids*,struct sst_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_send_pipe_module_params(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol)
{
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct sst_data *drv = snd_soc_component_get_drvdata(c);
	struct sst_ids *ids = w->priv;

	mutex_lock(&drv->lock);
	sst_find_and_send_pipe_algo(drv, w->name, ids);
	sst_set_pipe_gain(ids, drv, 0);
	mutex_unlock(&drv->lock);

	return 0;
}