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
struct nfs_fh {int dummy; } ;
struct nfs4_ff_layout_mirror {struct nfs_fh* fh_versions; } ;

/* Variables and functions */

struct nfs_fh *
nfs4_ff_layout_select_ds_fh(struct nfs4_ff_layout_mirror *mirror)
{
	/* FIXME: For now assume there is only 1 version available for the DS */
	return &mirror->fh_versions[0];
}