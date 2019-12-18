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
struct ceph_dir_file_info {scalar_t__ frag; int /*<<< orphan*/  last_readdir; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_frag_contains_value (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fpos_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpos_hash (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hash_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool need_send_readdir(struct ceph_dir_file_info *dfi, loff_t pos)
{
	if (!dfi->last_readdir)
		return true;
	if (is_hash_order(pos))
		return !ceph_frag_contains_value(dfi->frag, fpos_hash(pos));
	else
		return dfi->frag != fpos_frag(pos);
}