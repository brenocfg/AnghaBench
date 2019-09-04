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
struct TYPE_2__ {scalar_t__ client; } ;
struct snd_seq_port_subscribe {TYPE_1__ sender; } ;
struct snd_opl4 {int /*<<< orphan*/  access_mutex; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 scalar_t__ SNDRV_SEQ_CLIENT_SYSTEM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_opl4_seq_use_dec (struct snd_opl4*) ; 
 int /*<<< orphan*/  snd_opl4_synth_shutdown (struct snd_opl4*) ; 

__attribute__((used)) static int snd_opl4_seq_unuse(void *private_data, struct snd_seq_port_subscribe *info)
{
	struct snd_opl4 *opl4 = private_data;

	snd_opl4_synth_shutdown(opl4);

	mutex_lock(&opl4->access_mutex);
	opl4->used--;
	mutex_unlock(&opl4->access_mutex);

	if (info->sender.client != SNDRV_SEQ_CLIENT_SYSTEM)
		snd_opl4_seq_use_dec(opl4);
	return 0;
}