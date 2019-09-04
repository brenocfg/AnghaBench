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
struct TYPE_2__ {int f_flags; } ;
struct r_bin_coff_obj {TYPE_1__ hdr; } ;

/* Variables and functions */
 int COFF_FLAGS_TI_F_LNNO ; 
 int COFF_FLAGS_TI_F_LSYMS ; 
 int COFF_FLAGS_TI_F_RELFLG ; 

int r_coff_is_stripped(struct r_bin_coff_obj *obj) {
	return !!(obj->hdr.f_flags & (COFF_FLAGS_TI_F_RELFLG | \
		COFF_FLAGS_TI_F_LNNO | COFF_FLAGS_TI_F_LSYMS));
}