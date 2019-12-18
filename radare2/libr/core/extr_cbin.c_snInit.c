#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* name; char* classname; char* dname; int /*<<< orphan*/  vaddr; scalar_t__ paddr; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {TYPE_1__* bin; int /*<<< orphan*/  config; } ;
struct TYPE_10__ {char const* name; int /*<<< orphan*/ * demname; int /*<<< orphan*/ * demflag; int /*<<< orphan*/ * methflag; int /*<<< orphan*/ * methname; int /*<<< orphan*/ * classflag; int /*<<< orphan*/ * classname; void* nameflag; } ;
struct TYPE_9__ {int /*<<< orphan*/  cur; } ;
typedef  TYPE_2__ SymName ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RBinSymbol ;

/* Variables and functions */
 int MAXFLAG_LEN_DEFAULT ; 
 void* construct_symbol_flagname (char const*,int /*<<< orphan*/ *,int) ; 
 char* getPrefixFor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_bin_demangle (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * r_bin_symbol_name (TYPE_4__*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_name_filter (int /*<<< orphan*/ *,int) ; 
 void* r_str_newf (char*,int /*<<< orphan*/ *,char const*) ; 
 void* strdup (char*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snInit(RCore *r, SymName *sn, RBinSymbol *sym, const char *lang) {
	int bin_demangle = lang != NULL;
	bool keep_lib = r_config_get_i (r->config, "bin.demangle.libs");
	if (!r || !sym || !sym->name) {
		return;
	}
	sn->name = strdup (sym->name);
	const char *pfx = getPrefixFor (sym->type);
	sn->nameflag = construct_symbol_flagname (pfx, r_bin_symbol_name (sym), MAXFLAG_LEN_DEFAULT);
	if (sym->classname && sym->classname[0]) {
		sn->classname = strdup (sym->classname);
		sn->classflag = r_str_newf ("sym.%s.%s", sn->classname, sn->name);
		r_name_filter (sn->classflag, MAXFLAG_LEN_DEFAULT);
		const char *name = sym->dname? sym->dname: sym->name;
		sn->methname = r_str_newf ("%s::%s", sn->classname, name);
		sn->methflag = r_str_newf ("sym.%s.%s", sn->classname, name);
		r_name_filter (sn->methflag, strlen (sn->methflag));
	} else {
		sn->classname = NULL;
		sn->classflag = NULL;
		sn->methname = NULL;
		sn->methflag = NULL;
	}
	sn->demname = NULL;
	sn->demflag = NULL;
	if (bin_demangle && sym->paddr) {
		sn->demname = r_bin_demangle (r->bin->cur, lang, sn->name, sym->vaddr, keep_lib);
		if (sn->demname) {
			sn->demflag = construct_symbol_flagname (pfx, sn->demname, -1);
		}
	}
}