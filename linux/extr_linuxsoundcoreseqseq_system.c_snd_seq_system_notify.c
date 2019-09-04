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
struct TYPE_4__ {int client; int port; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_seq_event {TYPE_2__ dest; TYPE_1__ source; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_LENGTH_FIXED ; 
 int /*<<< orphan*/  announce_port ; 
 int snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysclient ; 

int snd_seq_system_notify(int client, int port, struct snd_seq_event *ev)
{
	ev->flags = SNDRV_SEQ_EVENT_LENGTH_FIXED;
	ev->source.client = sysclient;
	ev->source.port = announce_port;
	ev->dest.client = client;
	ev->dest.port = port;
	return snd_seq_kernel_client_dispatch(sysclient, ev, 0, 0);
}