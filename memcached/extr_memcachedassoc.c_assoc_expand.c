#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int verbose; } ;
struct TYPE_3__ {int hash_bytes; int hash_is_expanding; scalar_t__ hash_power_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ expand_bucket ; 
 int expanding ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hashpower ; 
 int hashsize (scalar_t__) ; 
 scalar_t__ old_hashtable ; 
 scalar_t__ primary_hashtable ; 
 TYPE_2__ settings ; 
 TYPE_1__ stats_state ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void assoc_expand(void) {
    old_hashtable = primary_hashtable;

    primary_hashtable = calloc(hashsize(hashpower + 1), sizeof(void *));
    if (primary_hashtable) {
        if (settings.verbose > 1)
            fprintf(stderr, "Hash table expansion starting\n");
        hashpower++;
        expanding = true;
        expand_bucket = 0;
        STATS_LOCK();
        stats_state.hash_power_level = hashpower;
        stats_state.hash_bytes += hashsize(hashpower) * sizeof(void *);
        stats_state.hash_is_expanding = true;
        STATS_UNLOCK();
    } else {
        primary_hashtable = old_hashtable;
        /* Bad news, but we can keep running. */
    }
}