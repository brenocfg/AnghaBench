#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct lowpan_iphc_ctx_table* private; } ;
struct lowpan_iphc_ctx_table {int /*<<< orphan*/  lock; TYPE_1__* table; } ;
struct TYPE_3__ {int /*<<< orphan*/  plen; int /*<<< orphan*/  pfx; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int LOWPAN_IPHC_CTX_TABLE_SIZE ; 
 int /*<<< orphan*/  lowpan_iphc_ctx_is_active (TYPE_1__*) ; 
 int /*<<< orphan*/  lowpan_iphc_ctx_is_compression (TYPE_1__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,char,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lowpan_context_show(struct seq_file *file, void *offset)
{
	struct lowpan_iphc_ctx_table *t = file->private;
	int i;

	seq_printf(file, "%3s|%-43s|%c\n", "cid", "prefix", 'C');
	seq_puts(file, "-------------------------------------------------\n");

	spin_lock_bh(&t->lock);
	for (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++) {
		if (!lowpan_iphc_ctx_is_active(&t->table[i]))
			continue;

		seq_printf(file, "%3d|%39pI6c/%-3d|%d\n", t->table[i].id,
			   &t->table[i].pfx, t->table[i].plen,
			   lowpan_iphc_ctx_is_compression(&t->table[i]));
	}
	spin_unlock_bh(&t->lock);

	return 0;
}