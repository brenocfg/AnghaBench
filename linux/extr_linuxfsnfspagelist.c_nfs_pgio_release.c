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
struct nfs_pgio_header {TYPE_1__* completion_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* completion ) (struct nfs_pgio_header*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 

__attribute__((used)) static void nfs_pgio_release(void *calldata)
{
	struct nfs_pgio_header *hdr = calldata;
	hdr->completion_ops->completion(hdr);
}