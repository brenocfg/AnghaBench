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
struct perm_bits {int /*<<< orphan*/  writefn; int /*<<< orphan*/  readfn; void* write; void* virt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_perm_bits (struct perm_bits*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  vfio_default_config_read ; 
 int /*<<< orphan*/  vfio_default_config_write ; 

__attribute__((used)) static int alloc_perm_bits(struct perm_bits *perm, int size)
{
	/*
	 * Round up all permission bits to the next dword, this lets us
	 * ignore whether a read/write exceeds the defined capability
	 * structure.  We can do this because:
	 *  - Standard config space is already dword aligned
	 *  - Capabilities are all dword aligned (bits 0:1 of next reserved)
	 *  - Express capabilities defined as dword aligned
	 */
	size = round_up(size, 4);

	/*
	 * Zero state is
	 * - All Readable, None Writeable, None Virtualized
	 */
	perm->virt = kzalloc(size, GFP_KERNEL);
	perm->write = kzalloc(size, GFP_KERNEL);
	if (!perm->virt || !perm->write) {
		free_perm_bits(perm);
		return -ENOMEM;
	}

	perm->readfn = vfio_default_config_read;
	perm->writefn = vfio_default_config_write;

	return 0;
}