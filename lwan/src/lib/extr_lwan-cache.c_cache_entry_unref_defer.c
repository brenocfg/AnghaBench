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
struct cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_unref (struct cache*,struct cache_entry*) ; 

__attribute__((used)) static void cache_entry_unref_defer(void *data1, void *data2)
{
    cache_entry_unref((struct cache *)data1, (struct cache_entry *)data2);
}