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
struct TYPE_2__ {int client; int port; } ;
struct snd_seq_event {TYPE_1__ dest; int /*<<< orphan*/  source; int /*<<< orphan*/  queue; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  addr; int /*<<< orphan*/  queue; } ;

/* Variables and functions */

__attribute__((used)) static inline void
snd_seq_oss_fill_addr(struct seq_oss_devinfo *dp, struct snd_seq_event *ev,
		     int dest_client, int dest_port)
{
	ev->queue = dp->queue;
	ev->source = dp->addr;
	ev->dest.client = dest_client;
	ev->dest.port = dest_port;
}