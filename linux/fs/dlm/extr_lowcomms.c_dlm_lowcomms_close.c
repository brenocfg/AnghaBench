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
struct dlm_node_addr {size_t addr_count; struct dlm_node_addr** addr; int /*<<< orphan*/  list; } ;
struct connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CLOSE ; 
 int /*<<< orphan*/  clean_one_writequeue (struct connection*) ; 
 int /*<<< orphan*/  close_connection (struct connection*,int,int,int) ; 
 int /*<<< orphan*/  dlm_node_addrs_spin ; 
 struct dlm_node_addr* find_node_addr (int) ; 
 int /*<<< orphan*/  kfree (struct dlm_node_addr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_print (char*,int) ; 
 struct connection* nodeid2con (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_lowcomms_close(int nodeid)
{
	struct connection *con;
	struct dlm_node_addr *na;

	log_print("closing connection to node %d", nodeid);
	con = nodeid2con(nodeid, 0);
	if (con) {
		set_bit(CF_CLOSE, &con->flags);
		close_connection(con, true, true, true);
		clean_one_writequeue(con);
	}

	spin_lock(&dlm_node_addrs_spin);
	na = find_node_addr(nodeid);
	if (na) {
		list_del(&na->list);
		while (na->addr_count--)
			kfree(na->addr[na->addr_count]);
		kfree(na);
	}
	spin_unlock(&dlm_node_addrs_spin);

	return 0;
}