#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_pgio_header {TYPE_1__* rw_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rw_free_header ) (struct nfs_pgio_header*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_pgio_data_destroy (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 

void nfs_pgio_header_free(struct nfs_pgio_header *hdr)
{
	nfs_pgio_data_destroy(hdr);
	hdr->rw_ops->rw_free_header(hdr);
}