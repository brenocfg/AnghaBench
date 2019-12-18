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
struct hsr_priv {int /*<<< orphan*/ * node_tbl_root; int /*<<< orphan*/ * node_tbl_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

void
hsr_debugfs_term(struct hsr_priv *priv)
{
	debugfs_remove(priv->node_tbl_file);
	priv->node_tbl_file = NULL;
	debugfs_remove(priv->node_tbl_root);
	priv->node_tbl_root = NULL;
}