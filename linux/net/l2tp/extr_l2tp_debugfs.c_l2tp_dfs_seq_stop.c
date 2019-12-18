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
struct seq_file {int dummy; } ;
struct l2tp_dfs_seq_data {int /*<<< orphan*/ * tunnel; int /*<<< orphan*/ * session; } ;

/* Variables and functions */
 struct l2tp_dfs_seq_data* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2tp_tunnel_dec_refcount (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2tp_dfs_seq_stop(struct seq_file *p, void *v)
{
	struct l2tp_dfs_seq_data *pd = v;

	if (!pd || pd == SEQ_START_TOKEN)
		return;

	/* Drop reference taken by last invocation of l2tp_dfs_next_session()
	 * or l2tp_dfs_next_tunnel().
	 */
	if (pd->session) {
		l2tp_session_dec_refcount(pd->session);
		pd->session = NULL;
	}
	if (pd->tunnel) {
		l2tp_tunnel_dec_refcount(pd->tunnel);
		pd->tunnel = NULL;
	}
}