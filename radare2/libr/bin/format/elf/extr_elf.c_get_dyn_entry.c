#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct TYPE_7__ {int dyn_entries; TYPE_1__* dyn_buf; } ;
struct TYPE_6__ {int d_ptr; int d_val; } ;
struct TYPE_5__ {int d_tag; TYPE_2__ d_un; } ;
typedef  TYPE_3__ ELFOBJ ;

/* Variables and functions */
#define  DT_JMPREL 134 
#define  DT_PLTGOT 133 
#define  DT_PLTRELSZ 132 
#define  DT_REL 131 
#define  DT_RELA 130 
#define  DT_RELASZ 129 
#define  DT_RELSZ 128 
 int /*<<< orphan*/  r_warn_if_reached () ; 

__attribute__((used)) static ut64 get_dyn_entry(ELFOBJ *bin, int dyn_entry) {
	int i;
	for (i = 0; i < bin->dyn_entries; i++) {
		if (bin->dyn_buf[i].d_tag == dyn_entry) {
			switch (bin->dyn_buf[i].d_tag) {
			case DT_REL:
			case DT_RELA:
			case DT_PLTGOT:
			case DT_JMPREL:
				return bin->dyn_buf[i].d_un.d_ptr;
			case DT_RELSZ:
			case DT_RELASZ:
			case DT_PLTRELSZ:
				return bin->dyn_buf[i].d_un.d_val;
			default:
				r_warn_if_reached ();
				break;
			}
		}
	}

	return -1;
}