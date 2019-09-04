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
struct snd_midi_op {int /*<<< orphan*/  (* nrpn ) (void*,struct snd_midi_channel*,struct snd_midi_channel_set*) ;} ;
struct snd_midi_channel_set {int dummy; } ;
struct snd_midi_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,struct snd_midi_channel*,struct snd_midi_channel_set*) ; 

__attribute__((used)) static void
nrpn(struct snd_midi_op *ops, void *drv, struct snd_midi_channel *chan,
     struct snd_midi_channel_set *chset)
{
	/* parse XG NRPNs here if possible */
	if (ops->nrpn)
		ops->nrpn(drv, chan, chset);
}