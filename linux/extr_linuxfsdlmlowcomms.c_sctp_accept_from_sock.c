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
struct socket {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct sctp_prim {int /*<<< orphan*/  ssp_addr; } ;
struct connection {int nodeid; int /*<<< orphan*/  sock_mutex; int /*<<< orphan*/  rwork; int /*<<< orphan*/  flags; void* rx_action; struct connection* othercon; scalar_t__ sock; int /*<<< orphan*/  swork; int /*<<< orphan*/  writequeue_lock; int /*<<< orphan*/  writequeue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_IS_OTHERCON ; 
 int /*<<< orphan*/  CF_READ_PENDING ; 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SCTP_PRIMARY_ADDR ; 
 int /*<<< orphan*/  add_sock (struct socket*,struct connection*) ; 
 int addr_to_nodeid (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  con_cache ; 
 int /*<<< orphan*/  connections_lock ; 
 int /*<<< orphan*/  dlm_allow_conn ; 
 int kernel_accept (scalar_t__,struct socket**,int /*<<< orphan*/ ) ; 
 int kernel_getsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 struct connection* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_print (char*,...) ; 
 int /*<<< orphan*/  make_sockaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (struct sctp_prim*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct connection* nodeid2con (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  process_recv_sockets ; 
 int /*<<< orphan*/  process_send_sockets ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* receive_from_sock ; 
 int /*<<< orphan*/  recv_workqueue ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sctp_accept_from_sock(struct connection *con)
{
	/* Check that the new node is in the lockspace */
	struct sctp_prim prim;
	int nodeid;
	int prim_len, ret;
	int addr_len;
	struct connection *newcon;
	struct connection *addcon;
	struct socket *newsock;

	mutex_lock(&connections_lock);
	if (!dlm_allow_conn) {
		mutex_unlock(&connections_lock);
		return -1;
	}
	mutex_unlock(&connections_lock);

	mutex_lock_nested(&con->sock_mutex, 0);

	ret = kernel_accept(con->sock, &newsock, O_NONBLOCK);
	if (ret < 0)
		goto accept_err;

	memset(&prim, 0, sizeof(struct sctp_prim));
	prim_len = sizeof(struct sctp_prim);

	ret = kernel_getsockopt(newsock, IPPROTO_SCTP, SCTP_PRIMARY_ADDR,
				(char *)&prim, &prim_len);
	if (ret < 0) {
		log_print("getsockopt/sctp_primary_addr failed: %d", ret);
		goto accept_err;
	}

	make_sockaddr(&prim.ssp_addr, 0, &addr_len);
	ret = addr_to_nodeid(&prim.ssp_addr, &nodeid);
	if (ret) {
		unsigned char *b = (unsigned char *)&prim.ssp_addr;

		log_print("reject connect from unknown addr");
		print_hex_dump_bytes("ss: ", DUMP_PREFIX_NONE,
				     b, sizeof(struct sockaddr_storage));
		goto accept_err;
	}

	newcon = nodeid2con(nodeid, GFP_NOFS);
	if (!newcon) {
		ret = -ENOMEM;
		goto accept_err;
	}

	mutex_lock_nested(&newcon->sock_mutex, 1);

	if (newcon->sock) {
		struct connection *othercon = newcon->othercon;

		if (!othercon) {
			othercon = kmem_cache_zalloc(con_cache, GFP_NOFS);
			if (!othercon) {
				log_print("failed to allocate incoming socket");
				mutex_unlock(&newcon->sock_mutex);
				ret = -ENOMEM;
				goto accept_err;
			}
			othercon->nodeid = nodeid;
			othercon->rx_action = receive_from_sock;
			mutex_init(&othercon->sock_mutex);
			INIT_LIST_HEAD(&othercon->writequeue);
			spin_lock_init(&othercon->writequeue_lock);
			INIT_WORK(&othercon->swork, process_send_sockets);
			INIT_WORK(&othercon->rwork, process_recv_sockets);
			set_bit(CF_IS_OTHERCON, &othercon->flags);
		}
		mutex_lock_nested(&othercon->sock_mutex, 2);
		if (!othercon->sock) {
			newcon->othercon = othercon;
			add_sock(newsock, othercon);
			addcon = othercon;
			mutex_unlock(&othercon->sock_mutex);
		} else {
			printk("Extra connection from node %d attempted\n", nodeid);
			ret = -EAGAIN;
			mutex_unlock(&othercon->sock_mutex);
			mutex_unlock(&newcon->sock_mutex);
			goto accept_err;
		}
	} else {
		newcon->rx_action = receive_from_sock;
		add_sock(newsock, newcon);
		addcon = newcon;
	}

	log_print("connected to %d", nodeid);

	mutex_unlock(&newcon->sock_mutex);

	/*
	 * Add it to the active queue in case we got data
	 * between processing the accept adding the socket
	 * to the read_sockets list
	 */
	if (!test_and_set_bit(CF_READ_PENDING, &addcon->flags))
		queue_work(recv_workqueue, &addcon->rwork);
	mutex_unlock(&con->sock_mutex);

	return 0;

accept_err:
	mutex_unlock(&con->sock_mutex);
	if (newsock)
		sock_release(newsock);
	if (ret != -EAGAIN)
		log_print("error accepting connection from node: %d", ret);

	return ret;
}