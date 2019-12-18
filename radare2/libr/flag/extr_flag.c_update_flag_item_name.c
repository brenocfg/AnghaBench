#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ht_name; } ;
struct TYPE_7__ {char const* name; } ;
typedef  TYPE_1__ RFlagItem ;
typedef  TYPE_2__ RFlag ;

/* Variables and functions */
 char* filter_item_name (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ht_pp_insert (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int ht_pp_update_key (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  set_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static bool update_flag_item_name(RFlag *f, RFlagItem *item, const char *newname, bool force) {
	if (!f || !item || !newname) {
		return false;
	}
	if (!force && (item->name == newname || (item->name && !strcmp (item->name, newname)))) {
		return false;
	}
	char *fname = filter_item_name (newname);
	if (!fname) {
		return false;
	}
	bool res = (item->name)
		? ht_pp_update_key (f->ht_name, item->name, fname)
		: ht_pp_insert (f->ht_name, fname, item);
	if (res) {
		set_name (item, fname);
		return true;
	}
	free (fname);
	return false;
}