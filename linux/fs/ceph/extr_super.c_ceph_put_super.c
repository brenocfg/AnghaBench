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
struct ceph_fs_client {int /*<<< orphan*/  mdsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_mdsc_close_sessions (int /*<<< orphan*/ ) ; 
 struct ceph_fs_client* ceph_sb_to_client (struct super_block*) ; 
 int /*<<< orphan*/  dout (char*) ; 

__attribute__((used)) static void ceph_put_super(struct super_block *s)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(s);

	dout("put_super\n");
	ceph_mdsc_close_sessions(fsc->mdsc);
}