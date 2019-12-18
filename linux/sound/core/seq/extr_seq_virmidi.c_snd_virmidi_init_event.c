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
struct snd_virmidi {int seq_mode; int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct snd_seq_event {int /*<<< orphan*/  type; TYPE_2__ dest; TYPE_1__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_ADDRESS_SUBSCRIBERS ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_NONE ; 
#define  SNDRV_VIRMIDI_SEQ_ATTACH 129 
#define  SNDRV_VIRMIDI_SEQ_DISPATCH 128 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_virmidi_init_event(struct snd_virmidi *vmidi,
				   struct snd_seq_event *ev)
{
	memset(ev, 0, sizeof(*ev));
	ev->source.port = vmidi->port;
	switch (vmidi->seq_mode) {
	case SNDRV_VIRMIDI_SEQ_DISPATCH:
		ev->dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
		break;
	case SNDRV_VIRMIDI_SEQ_ATTACH:
		/* FIXME: source and destination are same - not good.. */
		ev->dest.client = vmidi->client;
		ev->dest.port = vmidi->port;
		break;
	}
	ev->type = SNDRV_SEQ_EVENT_NONE;
}