#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* prev; struct TYPE_13__* next; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; TYPE_4__ ordered_list; TYPE_4__ list; } ;
typedef  TYPE_1__ pair_t ;
struct TYPE_11__ {int /*<<< orphan*/  size; TYPE_4__ list; TYPE_3__* buckets; int /*<<< orphan*/  order; } ;
typedef  TYPE_2__ hashtable_t ;
struct TYPE_12__ {TYPE_4__* last; TYPE_4__* first; } ;
typedef  TYPE_3__ bucket_t ;

/* Variables and functions */
 size_t hashmask (int /*<<< orphan*/ ) ; 
 TYPE_1__* hashtable_find_pair (TYPE_2__*,TYPE_3__*,char const*,size_t) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonp_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (TYPE_4__*) ; 

__attribute__((used)) static int hashtable_do_del(hashtable_t *hashtable,
                            const char *key, size_t hash)
{
    pair_t *pair;
    bucket_t *bucket;
    size_t index;

    index = hash & hashmask(hashtable->order);
    bucket = &hashtable->buckets[index];

    pair = hashtable_find_pair(hashtable, bucket, key, hash);
    if(!pair)
        return -1;

    if(&pair->list == bucket->first && &pair->list == bucket->last)
        bucket->first = bucket->last = &hashtable->list;

    else if(&pair->list == bucket->first)
        bucket->first = pair->list.next;

    else if(&pair->list == bucket->last)
        bucket->last = pair->list.prev;

    list_remove(&pair->list);
    list_remove(&pair->ordered_list);
    json_decref(pair->value);

    jsonp_free(pair);
    hashtable->size--;

    return 0;
}