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
struct TYPE_9__ {scalar_t__ root; } ;
struct TYPE_10__ {struct TYPE_10__* rwlock; struct TYPE_10__* stats; TYPE_1__ values_index; } ;
typedef  int /*<<< orphan*/  NAME_VALUE ;
typedef  TYPE_2__ DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  D_DICTIONARY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dictionary_name_value_destroy_nolock (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictionary_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  dictionary_write_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  freez (TYPE_2__*) ; 
 int /*<<< orphan*/  netdata_rwlock_destroy (TYPE_2__*) ; 

void dictionary_destroy(DICTIONARY *dict) {
    debug(D_DICTIONARY, "Destroying dictionary.");

    dictionary_write_lock(dict);

    while(dict->values_index.root)
        dictionary_name_value_destroy_nolock(dict, (NAME_VALUE *)dict->values_index.root);

    dictionary_unlock(dict);

    if(dict->stats)
        freez(dict->stats);

    if(dict->rwlock) {
        netdata_rwlock_destroy(dict->rwlock);
        freez(dict->rwlock);
    }

    freez(dict);
}