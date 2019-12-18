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
struct TYPE_3__ {void* value; } ;
typedef  TYPE_1__ NAME_VALUE ;
typedef  int /*<<< orphan*/  DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  D_DICTIONARY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* dictionary_name_value_index_find_nolock (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictionary_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void *dictionary_get(DICTIONARY *dict, const char *name) {
    debug(D_DICTIONARY, "GET dictionary entry with name '%s'.", name);

    dictionary_read_lock(dict);
    NAME_VALUE *nv = dictionary_name_value_index_find_nolock(dict, name, 0);
    dictionary_unlock(dict);

    if(unlikely(!nv)) {
        debug(D_DICTIONARY, "Not found dictionary entry with name '%s'.", name);
        return NULL;
    }

    debug(D_DICTIONARY, "Found dictionary entry with name '%s'.", name);
    return nv->value;
}