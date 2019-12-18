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
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  INO32 ; 
 int /*<<< orphan*/  ceph_ino_to_ino32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_sb_to_client (struct super_block*) ; 
 scalar_t__ ceph_test_mount_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ino_t ceph_translate_ino(struct super_block *sb, ino_t ino)
{
	if (ceph_test_mount_opt(ceph_sb_to_client(sb), INO32))
		ino = ceph_ino_to_ino32(ino);
	return ino;
}