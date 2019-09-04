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
struct pnfs_layout_hdr {int dummy; } ;
struct nfs4_flexfile_layout {struct pnfs_layout_hdr generic_hdr; int /*<<< orphan*/  last_report_time; int /*<<< orphan*/  mirrors; int /*<<< orphan*/  error_list; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 struct nfs4_flexfile_layout* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pnfs_layout_hdr *
ff_layout_alloc_layout_hdr(struct inode *inode, gfp_t gfp_flags)
{
	struct nfs4_flexfile_layout *ffl;

	ffl = kzalloc(sizeof(*ffl), gfp_flags);
	if (ffl) {
		INIT_LIST_HEAD(&ffl->error_list);
		INIT_LIST_HEAD(&ffl->mirrors);
		ffl->last_report_time = ktime_get();
		return &ffl->generic_hdr;
	} else
		return NULL;
}