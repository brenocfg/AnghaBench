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
struct snd_seq_port_subscribe {int flags; } ;
struct snd_seq_subscribers {int /*<<< orphan*/  dest_list; int /*<<< orphan*/  src_list; int /*<<< orphan*/  ref_count; struct snd_seq_port_subscribe info; } ;
struct snd_seq_client_port {int dummy; } ;
struct snd_seq_client {scalar_t__ number; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SNDRV_SEQ_PORT_SUBS_EXCLUSIVE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int check_and_subscribe_port (struct snd_seq_client*,struct snd_seq_client_port*,struct snd_seq_subscribers*,int,int,int) ; 
 int /*<<< orphan*/  delete_and_unsubscribe_port (struct snd_seq_client*,struct snd_seq_client_port*,struct snd_seq_subscribers*,int,int) ; 
 int /*<<< orphan*/  kfree (struct snd_seq_subscribers*) ; 
 struct snd_seq_subscribers* kzalloc (int,int /*<<< orphan*/ ) ; 

int snd_seq_port_connect(struct snd_seq_client *connector,
			 struct snd_seq_client *src_client,
			 struct snd_seq_client_port *src_port,
			 struct snd_seq_client *dest_client,
			 struct snd_seq_client_port *dest_port,
			 struct snd_seq_port_subscribe *info)
{
	struct snd_seq_subscribers *subs;
	bool exclusive;
	int err;

	subs = kzalloc(sizeof(*subs), GFP_KERNEL);
	if (!subs)
		return -ENOMEM;

	subs->info = *info;
	atomic_set(&subs->ref_count, 0);
	INIT_LIST_HEAD(&subs->src_list);
	INIT_LIST_HEAD(&subs->dest_list);

	exclusive = !!(info->flags & SNDRV_SEQ_PORT_SUBS_EXCLUSIVE);

	err = check_and_subscribe_port(src_client, src_port, subs, true,
				       exclusive,
				       connector->number != src_client->number);
	if (err < 0)
		goto error;
	err = check_and_subscribe_port(dest_client, dest_port, subs, false,
				       exclusive,
				       connector->number != dest_client->number);
	if (err < 0)
		goto error_dest;

	return 0;

 error_dest:
	delete_and_unsubscribe_port(src_client, src_port, subs, true,
				    connector->number != src_client->number);
 error:
	kfree(subs);
	return err;
}