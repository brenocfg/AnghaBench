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
struct list_head {int dummy; } ;
struct snd_seq_subscribers {int /*<<< orphan*/  info; struct list_head dest_list; struct list_head src_list; } ;
struct snd_seq_port_subs_info {int /*<<< orphan*/  list_mutex; int /*<<< orphan*/  list_lock; scalar_t__ exclusive; } ;
struct snd_seq_client_port {struct snd_seq_port_subs_info c_dest; struct snd_seq_port_subs_info c_src; } ;
struct snd_seq_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (struct list_head*) ; 
 int list_empty (struct list_head*) ; 
 int /*<<< orphan*/  unsubscribe_port (struct snd_seq_client*,struct snd_seq_client_port*,struct snd_seq_port_subs_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_and_unsubscribe_port(struct snd_seq_client *client,
					struct snd_seq_client_port *port,
					struct snd_seq_subscribers *subs,
					bool is_src, bool ack)
{
	struct snd_seq_port_subs_info *grp;
	struct list_head *list;
	bool empty;

	grp = is_src ? &port->c_src : &port->c_dest;
	list = is_src ? &subs->src_list : &subs->dest_list;
	down_write(&grp->list_mutex);
	write_lock_irq(&grp->list_lock);
	empty = list_empty(list);
	if (!empty)
		list_del_init(list);
	grp->exclusive = 0;
	write_unlock_irq(&grp->list_lock);

	if (!empty)
		unsubscribe_port(client, port, grp, &subs->info, ack);
	up_write(&grp->list_mutex);
}