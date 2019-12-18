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
struct nls_table {int /*<<< orphan*/  charset; } ;

/* Variables and functions */
 struct nls_table* load_nls_default () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (struct nls_table*) ; 

__attribute__((used)) static void
cifs_show_nls(struct seq_file *s, struct nls_table *cur)
{
	struct nls_table *def;

	/* Display iocharset= option if it's not default charset */
	def = load_nls_default();
	if (def != cur)
		seq_printf(s, ",iocharset=%s", cur->charset);
	unload_nls(def);
}