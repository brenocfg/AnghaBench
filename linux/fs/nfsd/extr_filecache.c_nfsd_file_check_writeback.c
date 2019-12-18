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
struct nfsd_file {struct file* nf_file; } ;
struct file {int f_mode; struct address_space* f_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 scalar_t__ mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nfsd_file_check_writeback(struct nfsd_file *nf)
{
	struct file *file = nf->nf_file;
	struct address_space *mapping;

	if (!file || !(file->f_mode & FMODE_WRITE))
		return false;
	mapping = file->f_mapping;
	return mapping_tagged(mapping, PAGECACHE_TAG_DIRTY) ||
		mapping_tagged(mapping, PAGECACHE_TAG_WRITEBACK);
}