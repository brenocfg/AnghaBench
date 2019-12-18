#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avl ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  values_index; } ;
struct TYPE_9__ {struct TYPE_9__* name; struct TYPE_9__* value; } ;
typedef  TYPE_1__ NAME_VALUE ;
typedef  TYPE_2__ DICTIONARY ;

/* Variables and functions */
 int DICTIONARY_FLAG_NAME_LINK_DONT_CLONE ; 
 int DICTIONARY_FLAG_VALUE_LINK_DONT_CLONE ; 
 int /*<<< orphan*/  D_DICTIONARY ; 
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  NETDATA_DICTIONARY_STATS_DELETES_PLUS1 (TYPE_2__*) ; 
 int /*<<< orphan*/  NETDATA_DICTIONARY_STATS_ENTRIES_MINUS1 (TYPE_2__*) ; 
 int /*<<< orphan*/ * avl_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dictionary_name_value_destroy_nolock(DICTIONARY *dict, NAME_VALUE *nv) {
    debug(D_DICTIONARY, "Destroying name value entry for name '%s'.", nv->name);

    NETDATA_DICTIONARY_STATS_DELETES_PLUS1(dict);
    if(unlikely(avl_remove(&(dict->values_index), (avl *)(nv)) != (avl *)nv))
        error("dictionary: INTERNAL ERROR: dictionary invalid removal of node.");

    NETDATA_DICTIONARY_STATS_ENTRIES_MINUS1(dict);

    if(!(dict->flags & DICTIONARY_FLAG_VALUE_LINK_DONT_CLONE)) {
        debug(D_REGISTRY, "Dictionary freeing value of '%s'", nv->name);
        freez(nv->value);
    }

    if(!(dict->flags & DICTIONARY_FLAG_NAME_LINK_DONT_CLONE)) {
        debug(D_REGISTRY, "Dictionary freeing name '%s'", nv->name);
        freez(nv->name);
    }

    freez(nv);
}