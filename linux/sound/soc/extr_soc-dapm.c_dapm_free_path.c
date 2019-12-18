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
struct snd_soc_dapm_path {int /*<<< orphan*/  list; int /*<<< orphan*/  list_kcontrol; int /*<<< orphan*/ * list_node; } ;

/* Variables and functions */
 size_t SND_SOC_DAPM_DIR_IN ; 
 size_t SND_SOC_DAPM_DIR_OUT ; 
 int /*<<< orphan*/  kfree (struct snd_soc_dapm_path*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dapm_free_path(struct snd_soc_dapm_path *path)
{
	list_del(&path->list_node[SND_SOC_DAPM_DIR_IN]);
	list_del(&path->list_node[SND_SOC_DAPM_DIR_OUT]);
	list_del(&path->list_kcontrol);
	list_del(&path->list);
	kfree(path);
}