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
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/ * r_list_new () ; 

__attribute__((used)) static RList* entries(RBinFile *bf) { //Should be 3 offsets pointed by NMI, RESET, IRQ after mapping && default = 1st CHR
	RList *ret;
	if (!(ret = r_list_new ())) {
		return NULL;
	}
	/*
	RBinAddr *ptr = NULL;
	if (!(ptr = R_NEW0 (RBinAddr))) {
		return ret;
	}
	ptr->paddr = INES_HDR_SIZE;
	ptr->vaddr = ROM_START_ADDRESS;
	r_list_append (ret, ptr);
	*/
	return ret;
}