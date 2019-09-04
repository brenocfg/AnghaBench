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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct ceph_vino {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_ino_compare ; 
 int /*<<< orphan*/  ceph_vino_to_ino (struct ceph_vino) ; 
 struct inode* ilookup5 (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ceph_vino*) ; 

__attribute__((used)) static inline struct inode *ceph_find_inode(struct super_block *sb,
					    struct ceph_vino vino)
{
	ino_t t = ceph_vino_to_ino(vino);
	return ilookup5(sb, t, ceph_ino_compare, &vino);
}