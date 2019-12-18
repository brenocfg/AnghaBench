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
struct squashfs_sb_info {int dummy; } ;
struct lz4_comp_opts {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERROR (char*) ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ LZ4_LEGACY ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *lz4_comp_opts(struct squashfs_sb_info *msblk,
	void *buff, int len)
{
	struct lz4_comp_opts *comp_opts = buff;

	/* LZ4 compressed filesystems always have compression options */
	if (comp_opts == NULL || len < sizeof(*comp_opts))
		return ERR_PTR(-EIO);

	if (le32_to_cpu(comp_opts->version) != LZ4_LEGACY) {
		/* LZ4 format currently used by the kernel is the 'legacy'
		 * format */
		ERROR("Unknown LZ4 version\n");
		return ERR_PTR(-EINVAL);
	}

	return NULL;
}