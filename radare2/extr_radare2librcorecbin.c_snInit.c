#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char const* name; char const* classname; char* dname; int /*<<< orphan*/  vaddr; scalar_t__ paddr; int /*<<< orphan*/  dup_count; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_1__* bin; } ;
struct TYPE_9__ {char const* name; char const* classname; char const* demname; int /*<<< orphan*/ * demflag; int /*<<< orphan*/ * methflag; int /*<<< orphan*/ * methname; int /*<<< orphan*/ * classflag; int /*<<< orphan*/ * nameflag; } ;
struct TYPE_8__ {int /*<<< orphan*/  cur; } ;
typedef  TYPE_2__ SymName ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RBinSymbol ;

/* Variables and functions */
 char* getPrefixFor (int /*<<< orphan*/ ) ; 
 char const* r_bin_demangle (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_name_filter (int /*<<< orphan*/ *,int) ; 
 void* r_str_newf (char*,char const*,char const*,...) ; 
 void* strdup (char const*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snInit(RCore *r, SymName *sn, RBinSymbol *sym, const char *lang) {
#define MAXFLAG_LEN 128
	int bin_demangle = lang != NULL;
	const char *pfx;
	if (!r || !sym || !sym->name) {
		return;
	}
	pfx = getPrefixFor (sym->type);
	sn->name = strdup (sym->name);
	if (sym->dup_count) {
		sn->nameflag = r_str_newf ("%s.%s_%d", pfx, sym->name, sym->dup_count);
	} else {
		sn->nameflag = r_str_newf ("%s.%s", pfx, sym->name);
	}
	r_name_filter (sn->nameflag, MAXFLAG_LEN);
	if (sym->classname && sym->classname[0]) {
		sn->classname = strdup (sym->classname);
		sn->classflag = r_str_newf ("sym.%s.%s", sn->classname, sn->name);
		r_name_filter (sn->classflag, MAXFLAG_LEN);
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
		sn->demname = r_bin_demangle (r->bin->cur, lang, sn->name, sym->vaddr);
		if (sn->demname) {
			sn->demflag = r_str_newf ("%s.%s", pfx, sn->demname);
			r_name_filter (sn->demflag, -1);
		}
	}
}