#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* prefix; struct TYPE_4__* next; } ;
typedef  TYPE_1__ PREFIX_STATS ;

/* Variables and functions */
 int PREFIX_HASH_SIZE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ num_prefixes ; 
 TYPE_1__** prefix_stats ; 
 scalar_t__ total_prefix_size ; 

void stats_prefix_clear() {
    int i;

    for (i = 0; i < PREFIX_HASH_SIZE; i++) {
        PREFIX_STATS *cur, *next;
        for (cur = prefix_stats[i]; cur != NULL; cur = next) {
            next = cur->next;
            free(cur->prefix);
            free(cur);
        }
        prefix_stats[i] = NULL;
    }
    num_prefixes = 0;
    total_prefix_size = 0;
}