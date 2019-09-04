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
struct TYPE_5__ {int f_nsyms; scalar_t__ f_nscns; } ;
struct r_bin_coff_obj {TYPE_2__* scn_hdrs; struct coff_symbol* symbols; TYPE_1__ hdr; } ;
struct coff_symbol {int n_sclass; scalar_t__ n_scnum; scalar_t__ n_value; } ;
struct TYPE_7__ {int size; scalar_t__ ordinal; scalar_t__ paddr; void* type; void* forwarder; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ s_scnptr; } ;
typedef  TYPE_3__ RBinSymbol ;

/* Variables and functions */
#define  COFF_SYM_CLASS_EXTERNAL 132 
#define  COFF_SYM_CLASS_FILE 131 
#define  COFF_SYM_CLASS_FUNCTION 130 
#define  COFF_SYM_CLASS_SECTION 129 
#define  COFF_SYM_CLASS_STATIC 128 
 char* R_BIN_TYPE_FUNC_STR ; 
 char* R_BIN_TYPE_SECTION_STR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_coff_symbol_name (struct r_bin_coff_obj*,struct coff_symbol*) ; 
 void* r_str_const (char*) ; 
 char* sdb_fmt (char*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static bool _fill_bin_symbol(struct r_bin_coff_obj *bin, int idx, RBinSymbol **sym) {
	RBinSymbol *ptr = *sym;
	char *coffname = NULL;
	struct coff_symbol *s = NULL;
	if (idx < 0 || idx > bin->hdr.f_nsyms) {
		return false;
	}
	if (!bin->symbols) {
		return false;
	}
	s = &bin->symbols[idx];
	coffname = r_coff_symbol_name (bin, s);
	if (!coffname) {
		return false;
	}
	ptr->name = strdup (coffname);
	free (coffname);
	ptr->forwarder = r_str_const ("NONE");

	switch (s->n_sclass) {
	case COFF_SYM_CLASS_FUNCTION:
		ptr->type = r_str_const (R_BIN_TYPE_FUNC_STR);
		break;
	case COFF_SYM_CLASS_FILE:
		ptr->type = r_str_const ("FILE");
		break;
	case COFF_SYM_CLASS_SECTION:
		ptr->type = r_str_const (R_BIN_TYPE_SECTION_STR);
		break;
	case COFF_SYM_CLASS_EXTERNAL:
		ptr->type = r_str_const ("EXTERNAL");
		break;
	case COFF_SYM_CLASS_STATIC:
		ptr->type = r_str_const ("STATIC");
		break;
	default:
		ptr->type = r_str_const (sdb_fmt ("%i", s->n_sclass));
		break;
	}
	if (bin->symbols[idx].n_scnum < bin->hdr.f_nscns &&
	    bin->symbols[idx].n_scnum > 0) {
		//first index is 0 that is why -1
		ptr->paddr = bin->scn_hdrs[s->n_scnum - 1].s_scnptr + s->n_value;
	}
	ptr->size = 4;
	ptr->ordinal = 0;
	return true;
}