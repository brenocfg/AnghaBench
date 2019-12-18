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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_meta_lvb {int /*<<< orphan*/  lvb_iattr; int /*<<< orphan*/  lvb_imtime_packed; int /*<<< orphan*/  lvb_ictime_packed; int /*<<< orphan*/  lvb_iatime_packed; int /*<<< orphan*/  lvb_inlink; int /*<<< orphan*/  lvb_imode; int /*<<< orphan*/  lvb_igid; int /*<<< orphan*/  lvb_iuid; int /*<<< orphan*/  lvb_isize; int /*<<< orphan*/  lvb_igeneration; int /*<<< orphan*/  lvb_iclusters; int /*<<< orphan*/  lvb_version; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_lksb; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 struct ocfs2_meta_lvb* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_dump_meta_lvb_info(u64 level,
				     const char *function,
				     unsigned int line,
				     struct ocfs2_lock_res *lockres)
{
	struct ocfs2_meta_lvb *lvb = ocfs2_dlm_lvb(&lockres->l_lksb);

	mlog(level, "LVB information for %s (called from %s:%u):\n",
	     lockres->l_name, function, line);
	mlog(level, "version: %u, clusters: %u, generation: 0x%x\n",
	     lvb->lvb_version, be32_to_cpu(lvb->lvb_iclusters),
	     be32_to_cpu(lvb->lvb_igeneration));
	mlog(level, "size: %llu, uid %u, gid %u, mode 0x%x\n",
	     (unsigned long long)be64_to_cpu(lvb->lvb_isize),
	     be32_to_cpu(lvb->lvb_iuid), be32_to_cpu(lvb->lvb_igid),
	     be16_to_cpu(lvb->lvb_imode));
	mlog(level, "nlink %u, atime_packed 0x%llx, ctime_packed 0x%llx, "
	     "mtime_packed 0x%llx iattr 0x%x\n", be16_to_cpu(lvb->lvb_inlink),
	     (long long)be64_to_cpu(lvb->lvb_iatime_packed),
	     (long long)be64_to_cpu(lvb->lvb_ictime_packed),
	     (long long)be64_to_cpu(lvb->lvb_imtime_packed),
	     be32_to_cpu(lvb->lvb_iattr));
}