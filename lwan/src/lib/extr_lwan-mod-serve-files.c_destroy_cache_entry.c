#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file_cache_entry {TYPE_1__* funcs; } ;
struct cache_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct file_cache_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct file_cache_entry*) ; 
 int /*<<< orphan*/  stub1 (struct file_cache_entry*) ; 

__attribute__((used)) static void destroy_cache_entry(struct cache_entry *entry,
                                void *context __attribute__((unused)))
{
    struct file_cache_entry *fce = (struct file_cache_entry *)entry;

    fce->funcs->free(fce);
    free(fce);
}