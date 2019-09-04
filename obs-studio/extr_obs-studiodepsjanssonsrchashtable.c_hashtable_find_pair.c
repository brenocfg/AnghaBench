#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t hash; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ pair_t ;
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_2__ list_t ;
typedef  int /*<<< orphan*/  hashtable_t ;
struct TYPE_11__ {TYPE_2__* last; TYPE_2__* first; } ;
typedef  TYPE_3__ bucket_t ;

/* Variables and functions */
 scalar_t__ bucket_is_empty (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_1__* list_to_pair (TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static pair_t *hashtable_find_pair(hashtable_t *hashtable, bucket_t *bucket,
                                   const char *key, size_t hash)
{
    list_t *list;
    pair_t *pair;

    if(bucket_is_empty(hashtable, bucket))
        return NULL;

    list = bucket->first;
    while(1)
    {
        pair = list_to_pair(list);
        if(pair->hash == hash && strcmp(pair->key, key) == 0)
            return pair;

        if(list == bucket->last)
            break;

        list = list->next;
    }

    return NULL;
}