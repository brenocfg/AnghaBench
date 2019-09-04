#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* data; int /*<<< orphan*/  log; TYPE_6__* cache; TYPE_3__* file; } ;
typedef  TYPE_1__ ngx_open_file_cache_event_t ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_9__ {int close; scalar_t__ use_event; int /*<<< orphan*/ * event; int /*<<< orphan*/  node; int /*<<< orphan*/  queue; } ;
typedef  TYPE_3__ ngx_cached_open_file_t ;
struct TYPE_10__ {int /*<<< orphan*/  current; int /*<<< orphan*/  rbtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_close_cached_file (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_open_file_cache_remove(ngx_event_t *ev)
{
    ngx_cached_open_file_t       *file;
    ngx_open_file_cache_event_t  *fev;

    fev = ev->data;
    file = fev->file;

    ngx_queue_remove(&file->queue);

    ngx_rbtree_delete(&fev->cache->rbtree, &file->node);

    fev->cache->current--;

    /* NGX_ONESHOT_EVENT was already deleted */
    file->event = NULL;
    file->use_event = 0;

    file->close = 1;

    ngx_close_cached_file(fev->cache, file, 0, ev->log);

    /* free memory only when fev->cache and fev->file are already not needed */

    ngx_free(ev->data);
    ngx_free(ev);
}