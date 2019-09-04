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
struct ext4_sb_info {unsigned long long s_cluster_bits; int /*<<< orphan*/  s_resv_clusters; int /*<<< orphan*/  s_es; } ;
typedef  size_t ssize_t ;
typedef  unsigned long long ext4_fsblk_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,unsigned long long) ; 
 unsigned long long ext4_blocks_count (int /*<<< orphan*/ ) ; 
 int kstrtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  skip_spaces (char const*) ; 

__attribute__((used)) static ssize_t reserved_clusters_store(struct ext4_sb_info *sbi,
				   const char *buf, size_t count)
{
	unsigned long long val;
	ext4_fsblk_t clusters = (ext4_blocks_count(sbi->s_es) >>
				 sbi->s_cluster_bits);
	int ret;

	ret = kstrtoull(skip_spaces(buf), 0, &val);
	if (ret || val >= clusters)
		return -EINVAL;

	atomic64_set(&sbi->s_resv_clusters, val);
	return count;
}