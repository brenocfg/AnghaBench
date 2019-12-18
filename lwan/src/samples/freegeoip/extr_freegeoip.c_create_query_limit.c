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
struct query_limit {scalar_t__ queries; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIKELY (struct query_limit*) ; 
 struct query_limit* malloc (int) ; 

__attribute__((used)) static struct cache_entry *create_query_limit(const char *key
                                              __attribute__((unused)),
                                              void *context
                                              __attribute__((unused)))
{
    struct query_limit *entry = malloc(sizeof(*entry));
    if (LIKELY(entry))
        entry->queries = 0;
    return (struct cache_entry *)entry;
}