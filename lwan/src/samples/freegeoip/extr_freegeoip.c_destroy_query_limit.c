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
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cache_entry*) ; 

__attribute__((used)) static void destroy_query_limit(struct cache_entry *entry,
                                void *context __attribute__((unused)))
{
    free(entry);
}