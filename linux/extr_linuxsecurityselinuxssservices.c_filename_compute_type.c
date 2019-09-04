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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct policydb {int /*<<< orphan*/  filename_trans; int /*<<< orphan*/  filename_trans_ttypes; } ;
struct filename_trans_datum {int /*<<< orphan*/  otype; } ;
struct filename_trans {char const* name; int /*<<< orphan*/  tclass; void* ttype; void* stype; } ;
struct context {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebitmap_get_bit (int /*<<< orphan*/ *,void*) ; 
 struct filename_trans_datum* hashtab_search (int /*<<< orphan*/ ,struct filename_trans*) ; 

__attribute__((used)) static void filename_compute_type(struct policydb *policydb,
				  struct context *newcontext,
				  u32 stype, u32 ttype, u16 tclass,
				  const char *objname)
{
	struct filename_trans ft;
	struct filename_trans_datum *otype;

	/*
	 * Most filename trans rules are going to live in specific directories
	 * like /dev or /var/run.  This bitmap will quickly skip rule searches
	 * if the ttype does not contain any rules.
	 */
	if (!ebitmap_get_bit(&policydb->filename_trans_ttypes, ttype))
		return;

	ft.stype = stype;
	ft.ttype = ttype;
	ft.tclass = tclass;
	ft.name = objname;

	otype = hashtab_search(policydb->filename_trans, &ft);
	if (otype)
		newcontext->type = otype->otype;
}