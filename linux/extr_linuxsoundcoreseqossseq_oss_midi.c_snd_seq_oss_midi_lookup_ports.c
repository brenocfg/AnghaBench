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
struct snd_seq_port_info {int client; TYPE_1__ addr; } ;
struct snd_seq_client_info {int client; TYPE_1__ addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT ; 
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT ; 
 int /*<<< orphan*/  kfree (struct snd_seq_port_info*) ; 
 struct snd_seq_port_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_seq_kernel_client_ctl (int,int /*<<< orphan*/ ,struct snd_seq_port_info*) ; 
 int /*<<< orphan*/  snd_seq_oss_midi_check_new_port (struct snd_seq_port_info*) ; 

int
snd_seq_oss_midi_lookup_ports(int client)
{
	struct snd_seq_client_info *clinfo;
	struct snd_seq_port_info *pinfo;

	clinfo = kzalloc(sizeof(*clinfo), GFP_KERNEL);
	pinfo = kzalloc(sizeof(*pinfo), GFP_KERNEL);
	if (! clinfo || ! pinfo) {
		kfree(clinfo);
		kfree(pinfo);
		return -ENOMEM;
	}
	clinfo->client = -1;
	while (snd_seq_kernel_client_ctl(client, SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT, clinfo) == 0) {
		if (clinfo->client == client)
			continue; /* ignore myself */
		pinfo->addr.client = clinfo->client;
		pinfo->addr.port = -1;
		while (snd_seq_kernel_client_ctl(client, SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT, pinfo) == 0)
			snd_seq_oss_midi_check_new_port(pinfo);
	}
	kfree(clinfo);
	kfree(pinfo);
	return 0;
}