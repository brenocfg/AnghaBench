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
struct snd_kcontrol_new {int dummy; } ;
struct nid_path {int dummy; } ;
struct hda_gen_spec {int /*<<< orphan*/  pcm_mutex; int /*<<< orphan*/  loopback_list; int /*<<< orphan*/  paths; int /*<<< orphan*/  kctls; } ;
struct hda_amp_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_array_init (int /*<<< orphan*/ *,int,int) ; 

int snd_hda_gen_spec_init(struct hda_gen_spec *spec)
{
	snd_array_init(&spec->kctls, sizeof(struct snd_kcontrol_new), 32);
	snd_array_init(&spec->paths, sizeof(struct nid_path), 8);
	snd_array_init(&spec->loopback_list, sizeof(struct hda_amp_list), 8);
	mutex_init(&spec->pcm_mutex);
	return 0;
}