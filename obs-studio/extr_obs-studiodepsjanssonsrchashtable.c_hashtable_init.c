#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  list; TYPE_2__* buckets; int /*<<< orphan*/  order; int /*<<< orphan*/  ordered_list; scalar_t__ size; } ;
typedef  TYPE_1__ hashtable_t ;
typedef  int /*<<< orphan*/  bucket_t ;
struct TYPE_5__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; } ;

/* Variables and functions */
 int /*<<< orphan*/  INITIAL_HASHTABLE_ORDER ; 
 size_t hashsize (int /*<<< orphan*/ ) ; 
 TYPE_2__* jsonp_malloc (int) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

int hashtable_init(hashtable_t *hashtable)
{
    size_t i;

    hashtable->size = 0;
    hashtable->order = INITIAL_HASHTABLE_ORDER;
    hashtable->buckets = jsonp_malloc(hashsize(hashtable->order) * sizeof(bucket_t));
    if(!hashtable->buckets)
        return -1;

    list_init(&hashtable->list);
    list_init(&hashtable->ordered_list);

    for(i = 0; i < hashsize(hashtable->order); i++)
    {
        hashtable->buckets[i].first = hashtable->buckets[i].last =
            &hashtable->list;
    }

    return 0;
}