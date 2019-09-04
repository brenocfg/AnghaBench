#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct cpu_key {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 int /*<<< orphan*/  _make_cpu_key (struct cpu_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_inode_item_key_version (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

void make_cpu_key(struct cpu_key *key, struct inode *inode, loff_t offset,
		  int type, int length)
{
	_make_cpu_key(key, get_inode_item_key_version(inode),
		      le32_to_cpu(INODE_PKEY(inode)->k_dir_id),
		      le32_to_cpu(INODE_PKEY(inode)->k_objectid), offset, type,
		      length);
}