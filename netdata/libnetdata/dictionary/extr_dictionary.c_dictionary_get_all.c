#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  root; } ;
struct TYPE_7__ {TYPE_1__ values_index; } ;
typedef  TYPE_2__ DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  dictionary_read_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  dictionary_unlock (TYPE_2__*) ; 
 int dictionary_walker (int /*<<< orphan*/ ,int (*) (void*,void*),void*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

int dictionary_get_all(DICTIONARY *dict, int (*callback)(void *entry, void *data), void *data) {
    int ret = 0;

    dictionary_read_lock(dict);

    if(likely(dict->values_index.root))
        ret = dictionary_walker(dict->values_index.root, callback, data);

    dictionary_unlock(dict);

    return ret;
}