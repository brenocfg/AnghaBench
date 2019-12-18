#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* xtr_type; int /*<<< orphan*/ * libname; int /*<<< orphan*/ * type; int /*<<< orphan*/ * machine; scalar_t__ bits; int /*<<< orphan*/ * arch; } ;
typedef  TYPE_1__ RBinXtrMetadata ;

/* Variables and functions */

__attribute__((used)) static void fill_metadata_info_from_hdr(RBinXtrMetadata *meta, void *foo) {// struct Pe_32_r_bin_pemixed_obj_t* pe_bin){
	meta->arch = NULL;
	meta->bits = 0;
	meta->machine = NULL;
	meta->type = NULL;
	meta->libname = NULL;
	meta->xtr_type = "net";
	//strcpy (meta->xtr_type, "net");
}