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
struct sockaddr_rxrpc {int /*<<< orphan*/  transport; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int afs_proc_cell_vlservers_show(struct seq_file *m, void *v)
{
	struct sockaddr_rxrpc *addr = v;

	/* display header on line 1 */
	if (v == (void *)1) {
		seq_puts(m, "ADDRESS\n");
		return 0;
	}

	/* display one cell per line on subsequent lines */
	seq_printf(m, "%pISp\n", &addr->transport);
	return 0;
}