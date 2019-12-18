#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pagevec; scalar_t__ page_array; } ;
struct TYPE_3__ {scalar_t__ context; } ;
struct nfs_pgio_header {TYPE_2__ page_array; TYPE_1__ args; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  put_nfs_open_context (scalar_t__) ; 

__attribute__((used)) static void nfs_pgio_data_destroy(struct nfs_pgio_header *hdr)
{
	if (hdr->args.context)
		put_nfs_open_context(hdr->args.context);
	if (hdr->page_array.pagevec != hdr->page_array.page_array)
		kfree(hdr->page_array.pagevec);
}