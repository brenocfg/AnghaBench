#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct r_bin_te_obj_t {TYPE_1__* header; } ;
struct TYPE_6__ {scalar_t__ vaddr; int /*<<< orphan*/  paddr; } ;
struct TYPE_5__ {scalar_t__ AddressOfEntryPoint; scalar_t__ ImageBase; } ;
typedef  TYPE_2__ RBinAddr ;

/* Variables and functions */
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ r_bin_te_get_stripped_delta (struct r_bin_te_obj_t*) ; 
 int /*<<< orphan*/  r_bin_te_vaddr_to_paddr (struct r_bin_te_obj_t*,scalar_t__) ; 

RBinAddr* r_bin_te_get_entrypoint(struct r_bin_te_obj_t* bin) {
	RBinAddr *entry = NULL;

	if (!bin || !bin->header) {
		return NULL;
	}
	if (!(entry = malloc (sizeof (RBinAddr)))) {
		perror("malloc (entrypoint)");
		return NULL;
	}
	entry->vaddr = bin->header->AddressOfEntryPoint - r_bin_te_get_stripped_delta (bin);
	if (entry->vaddr == 0) { // in TE if EP = 0 then EP = baddr
		entry->vaddr = bin->header->ImageBase;
	}
	entry->paddr = r_bin_te_vaddr_to_paddr (bin, entry->vaddr);
	return entry;
}