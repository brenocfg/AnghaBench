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
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {struct batadv_socket_client* private_data; } ;
struct batadv_socket_client {unsigned int index; int /*<<< orphan*/  queue_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  bat_priv; scalar_t__ queue_len; int /*<<< orphan*/  queue_list; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct batadv_socket_client**) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EXFULL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  batadv_debugfs_deprecated (struct file*,char*) ; 
 struct batadv_socket_client** batadv_socket_client_hash ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct batadv_socket_client*) ; 
 struct batadv_socket_client* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_socket_open(struct inode *inode, struct file *file)
{
	unsigned int i;
	struct batadv_socket_client *socket_client;

	if (!try_module_get(THIS_MODULE))
		return -EBUSY;

	batadv_debugfs_deprecated(file, "");

	stream_open(inode, file);

	socket_client = kmalloc(sizeof(*socket_client), GFP_KERNEL);
	if (!socket_client) {
		module_put(THIS_MODULE);
		return -ENOMEM;
	}

	for (i = 0; i < ARRAY_SIZE(batadv_socket_client_hash); i++) {
		if (!batadv_socket_client_hash[i]) {
			batadv_socket_client_hash[i] = socket_client;
			break;
		}
	}

	if (i == ARRAY_SIZE(batadv_socket_client_hash)) {
		pr_err("Error - can't add another packet client: maximum number of clients reached\n");
		kfree(socket_client);
		module_put(THIS_MODULE);
		return -EXFULL;
	}

	INIT_LIST_HEAD(&socket_client->queue_list);
	socket_client->queue_len = 0;
	socket_client->index = i;
	socket_client->bat_priv = inode->i_private;
	spin_lock_init(&socket_client->lock);
	init_waitqueue_head(&socket_client->queue_wait);

	file->private_data = socket_client;

	return 0;
}