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
typedef  int uint8_t ;
struct dictionary_stats {int dummy; } ;
typedef  int /*<<< orphan*/  netdata_rwlock_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  values_index; void* rwlock; void* stats; } ;
typedef  TYPE_1__ DICTIONARY ;

/* Variables and functions */
 int DICTIONARY_FLAG_SINGLE_THREADED ; 
 int DICTIONARY_FLAG_WITH_STATISTICS ; 
 int /*<<< orphan*/  D_DICTIONARY ; 
 int /*<<< orphan*/  avl_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  name_value_compare ; 
 int /*<<< orphan*/  netdata_rwlock_init (void*) ; 

DICTIONARY *dictionary_create(uint8_t flags) {
    debug(D_DICTIONARY, "Creating dictionary.");

    DICTIONARY *dict = callocz(1, sizeof(DICTIONARY));

    if(flags & DICTIONARY_FLAG_WITH_STATISTICS)
        dict->stats = callocz(1, sizeof(struct dictionary_stats));

    if(!(flags & DICTIONARY_FLAG_SINGLE_THREADED)) {
        dict->rwlock = callocz(1, sizeof(netdata_rwlock_t));
        netdata_rwlock_init(dict->rwlock);
    }

    avl_init(&dict->values_index, name_value_compare);
    dict->flags = flags;

    return dict;
}