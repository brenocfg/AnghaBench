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
struct nfs_pgio_header {int /*<<< orphan*/  rw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs_pgio_header* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfs_pgio_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_wdata_mempool ; 

__attribute__((used)) static struct nfs_pgio_header *nfs_writehdr_alloc(void)
{
	struct nfs_pgio_header *p = mempool_alloc(nfs_wdata_mempool, GFP_KERNEL);

	memset(p, 0, sizeof(*p));
	p->rw_mode = FMODE_WRITE;
	return p;
}