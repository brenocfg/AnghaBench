#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* cache_prefix; struct TYPE_5__* path; int /*<<< orphan*/  mutex; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ cache_container ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_container_close_index (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_container_delete_container(cache_container *pContainer)
{
    list_remove(&pContainer->entry);

    cache_container_close_index(pContainer);
    CloseHandle(pContainer->mutex);
    heap_free(pContainer->path);
    heap_free(pContainer->cache_prefix);
    heap_free(pContainer);
}