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
typedef  int /*<<< orphan*/  NAME_VALUE ;
typedef  int /*<<< orphan*/  DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  D_DICTIONARY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  dictionary_name_value_destroy_nolock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictionary_name_value_index_find_nolock (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictionary_write_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int dictionary_del(DICTIONARY *dict, const char *name) {
    int ret;

    debug(D_DICTIONARY, "DEL dictionary entry with name '%s'.", name);

    dictionary_write_lock(dict);

    NAME_VALUE *nv = dictionary_name_value_index_find_nolock(dict, name, 0);
    if(unlikely(!nv)) {
        debug(D_DICTIONARY, "Not found dictionary entry with name '%s'.", name);
        ret = -1;
    }
    else {
        debug(D_DICTIONARY, "Found dictionary entry with name '%s'.", name);
        dictionary_name_value_destroy_nolock(dict, nv);
        ret = 0;
    }

    dictionary_unlock(dict);

    return ret;
}