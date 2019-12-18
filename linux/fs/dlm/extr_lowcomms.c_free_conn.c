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
struct connection {int /*<<< orphan*/  list; struct connection* othercon; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_connection (struct connection*,int,int,int) ; 
 int /*<<< orphan*/  con_cache ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct connection*) ; 

__attribute__((used)) static void free_conn(struct connection *con)
{
	close_connection(con, true, true, true);
	if (con->othercon)
		kmem_cache_free(con_cache, con->othercon);
	hlist_del(&con->list);
	kmem_cache_free(con_cache, con);
}