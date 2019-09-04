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
struct isofs_iget5_callback_data {int /*<<< orphan*/  offset; int /*<<< orphan*/  block; } ;
struct iso_inode_info {int /*<<< orphan*/  i_iget5_offset; int /*<<< orphan*/  i_iget5_block; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct iso_inode_info* ISOFS_I (struct inode*) ; 

__attribute__((used)) static int isofs_iget5_set(struct inode *ino, void *data)
{
	struct iso_inode_info *i = ISOFS_I(ino);
	struct isofs_iget5_callback_data *d =
		(struct isofs_iget5_callback_data*)data;
	i->i_iget5_block = d->block;
	i->i_iget5_offset = d->offset;
	return 0;
}