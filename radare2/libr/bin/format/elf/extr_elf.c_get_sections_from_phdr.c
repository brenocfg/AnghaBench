#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_11__ {int /*<<< orphan*/  e_phnum; } ;
struct TYPE_15__ {int dyn_entries; TYPE_3__* dyn_buf; TYPE_1__ ehdr; scalar_t__ phdr; } ;
struct TYPE_14__ {int last; } ;
struct TYPE_12__ {int /*<<< orphan*/  d_ptr; int /*<<< orphan*/  d_val; } ;
struct TYPE_13__ {int d_tag; TYPE_2__ d_un; } ;
typedef  TYPE_4__ RBinElfSection ;
typedef  TYPE_5__ ELFOBJ ;

/* Variables and functions */
#define  DT_JMPREL 134 
#define  DT_PLTGOT 133 
#define  DT_PLTRELSZ 132 
#define  DT_REL 131 
#define  DT_RELA 130 
#define  DT_RELASZ 129 
#define  DT_RELSZ 128 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  create_section_from_phdr (TYPE_5__*,TYPE_4__*,int*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RBinElfSection *get_sections_from_phdr(ELFOBJ *bin) {
	RBinElfSection *ret;
	int i, num_sections = 0;
	ut64 reldyn = 0, relava = 0, pltgotva = 0, relva = 0;
	ut64 reldynsz = 0, relasz = 0, pltgotsz = 0;
	r_return_val_if_fail (bin && bin->phdr, NULL);
	if (!bin->ehdr.e_phnum || !bin->dyn_buf) {
		return NULL;
	}

	for (i = 0; i < bin->dyn_entries; i++) {
		switch (bin->dyn_buf[i].d_tag) {
		case DT_REL:
			reldyn = bin->dyn_buf[i].d_un.d_ptr;
			num_sections++;
			break;
		case DT_RELA:
			relva = bin->dyn_buf[i].d_un.d_ptr;
			num_sections++;
			break;
		case DT_RELSZ:
			reldynsz = bin->dyn_buf[i].d_un.d_val;
			break;
		case DT_RELASZ:
			relasz = bin->dyn_buf[i].d_un.d_val;
			break;
		case DT_PLTGOT:
			pltgotva = bin->dyn_buf[i].d_un.d_ptr;
			num_sections++;
			break;
		case DT_PLTRELSZ:
			pltgotsz = bin->dyn_buf[i].d_un.d_val;
			break;
		case DT_JMPREL:
			relava = bin->dyn_buf[i].d_un.d_ptr;
			num_sections++;
			break;
		default: break;
		}
	}
	ret = calloc (num_sections + 1, sizeof(RBinElfSection));
	if (!ret) {
		return NULL;
	}
	i = 0;
	create_section_from_phdr (bin, ret, &i, ".rel.dyn", reldyn, reldynsz);
	create_section_from_phdr (bin, ret, &i, ".rela.plt", relava, pltgotsz);
	create_section_from_phdr (bin, ret, &i, ".rel.plt", relva, relasz);
	create_section_from_phdr (bin, ret, &i, ".got.plt", pltgotva, pltgotsz);
	ret[i].last = 1;
	return ret;
}