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
struct ubifs_znode {int dummy; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubifs_dump_znode (struct ubifs_info*,struct ubifs_znode*) ; 

__attribute__((used)) static int dump_znode(struct ubifs_info *c, struct ubifs_znode *znode,
		      void *priv)
{
	ubifs_dump_znode(c, znode);
	return 0;
}