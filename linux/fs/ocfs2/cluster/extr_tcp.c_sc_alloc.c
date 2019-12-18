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
struct page {int dummy; } ;
struct o2nm_node {int /*<<< orphan*/  nd_item; } ;
struct o2net_sock_container {struct page* sc_page; int /*<<< orphan*/  sc_idle_timeout; int /*<<< orphan*/  sc_keepalive_work; int /*<<< orphan*/  sc_shutdown_work; int /*<<< orphan*/  sc_rx_work; int /*<<< orphan*/  sc_connect_work; struct o2nm_node* sc_node; int /*<<< orphan*/  sc_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct o2net_sock_container*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct o2net_sock_container* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  o2net_debug_add_sc (struct o2net_sock_container*) ; 
 int /*<<< orphan*/  o2net_idle_timer ; 
 int /*<<< orphan*/  o2net_rx_until_empty ; 
 int /*<<< orphan*/  o2net_sc_connect_completed ; 
 int /*<<< orphan*/  o2net_sc_send_keep_req ; 
 int /*<<< orphan*/  o2net_shutdown_sc ; 
 int o2nm_depend_item (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2nm_node_get (struct o2nm_node*) ; 
 int /*<<< orphan*/  o2nm_node_put (struct o2nm_node*) ; 
 int /*<<< orphan*/  sclog (struct o2net_sock_container*,char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct o2net_sock_container *sc_alloc(struct o2nm_node *node)
{
	struct o2net_sock_container *sc, *ret = NULL;
	struct page *page = NULL;
	int status = 0;

	page = alloc_page(GFP_NOFS);
	sc = kzalloc(sizeof(*sc), GFP_NOFS);
	if (sc == NULL || page == NULL)
		goto out;

	kref_init(&sc->sc_kref);
	o2nm_node_get(node);
	sc->sc_node = node;

	/* pin the node item of the remote node */
	status = o2nm_depend_item(&node->nd_item);
	if (status) {
		mlog_errno(status);
		o2nm_node_put(node);
		goto out;
	}
	INIT_WORK(&sc->sc_connect_work, o2net_sc_connect_completed);
	INIT_WORK(&sc->sc_rx_work, o2net_rx_until_empty);
	INIT_WORK(&sc->sc_shutdown_work, o2net_shutdown_sc);
	INIT_DELAYED_WORK(&sc->sc_keepalive_work, o2net_sc_send_keep_req);

	timer_setup(&sc->sc_idle_timeout, o2net_idle_timer, 0);

	sclog(sc, "alloced\n");

	ret = sc;
	sc->sc_page = page;
	o2net_debug_add_sc(sc);
	sc = NULL;
	page = NULL;

out:
	if (page)
		__free_page(page);
	kfree(sc);

	return ret;
}