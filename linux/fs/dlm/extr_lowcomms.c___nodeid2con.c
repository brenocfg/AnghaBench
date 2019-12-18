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
struct connection {int nodeid; int /*<<< orphan*/  rx_action; int /*<<< orphan*/  connect_action; int /*<<< orphan*/  rwork; int /*<<< orphan*/  swork; int /*<<< orphan*/  writequeue_lock; int /*<<< orphan*/  writequeue; int /*<<< orphan*/  sock_mutex; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct connection* __find_con (int) ; 
 int /*<<< orphan*/  con_cache ; 
 int /*<<< orphan*/ * connection_hash ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct connection* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nodeid_hash (int) ; 
 int /*<<< orphan*/  process_recv_sockets ; 
 int /*<<< orphan*/  process_send_sockets ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct connection *__nodeid2con(int nodeid, gfp_t alloc)
{
	struct connection *con = NULL;
	int r;

	con = __find_con(nodeid);
	if (con || !alloc)
		return con;

	con = kmem_cache_zalloc(con_cache, alloc);
	if (!con)
		return NULL;

	r = nodeid_hash(nodeid);
	hlist_add_head(&con->list, &connection_hash[r]);

	con->nodeid = nodeid;
	mutex_init(&con->sock_mutex);
	INIT_LIST_HEAD(&con->writequeue);
	spin_lock_init(&con->writequeue_lock);
	INIT_WORK(&con->swork, process_send_sockets);
	INIT_WORK(&con->rwork, process_recv_sockets);

	/* Setup action pointers for child sockets */
	if (con->nodeid) {
		struct connection *zerocon = __find_con(0);

		con->connect_action = zerocon->connect_action;
		if (!con->rx_action)
			con->rx_action = zerocon->rx_action;
	}

	return con;
}