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
struct nfs_pgio_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_free (struct nfs_pgio_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_wdata_mempool ; 

__attribute__((used)) static void nfs_writehdr_free(struct nfs_pgio_header *hdr)
{
	mempool_free(hdr, nfs_wdata_mempool);
}