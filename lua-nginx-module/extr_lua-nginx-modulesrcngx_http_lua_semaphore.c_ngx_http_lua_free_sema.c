#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  chain; TYPE_3__* block; } ;
typedef  TYPE_1__ ngx_http_lua_sema_t ;
struct TYPE_10__ {int used; scalar_t__ cur_epoch; int total; int num_per_block; int /*<<< orphan*/  free_queue; } ;
typedef  TYPE_2__ ngx_http_lua_sema_mm_t ;
struct TYPE_11__ {scalar_t__ used; scalar_t__ epoch; TYPE_2__* mm; } ;
typedef  TYPE_3__ ngx_http_lua_sema_mm_block_t ;
struct TYPE_12__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,int) ; 
 TYPE_8__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_free (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_free_sema(ngx_http_lua_sema_t *sem)
{
    ngx_http_lua_sema_t            *iter;
    ngx_uint_t                      i, mid_epoch;
    ngx_http_lua_sema_mm_block_t   *block;
    ngx_http_lua_sema_mm_t         *mm;

    block = sem->block;
    block->used--;

    mm = block->mm;
    mm->used--;

    mid_epoch = mm->cur_epoch - ((mm->total / mm->num_per_block) >> 1);

    if (block->epoch < mid_epoch) {
        ngx_queue_insert_tail(&mm->free_queue, &sem->chain);
        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "add to free queue tail semaphore: %p epoch: %d"
                       "mid_epoch: %d cur_epoch: %d", sem, (int) block->epoch,
                       (int) mid_epoch, (int) mm->cur_epoch);

    } else {
        ngx_queue_insert_head(&mm->free_queue, &sem->chain);
        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "add to free queue head semaphore: %p epoch: %d"
                       "mid_epoch: %d cur_epoch: %d", sem, (int) block->epoch,
                       (int) mid_epoch, (int) mm->cur_epoch);
    }

    dd("used: %d", (int) block->used);

    if (block->used == 0
        && mm->used <= (mm->total >> 1)
        && block->epoch < mid_epoch)
    {
        /* load <= 50% and it's on the older side */
        iter = (ngx_http_lua_sema_t *) (block + 1);

        for (i = 0; i < mm->num_per_block; i++, iter++) {
            ngx_queue_remove(&iter->chain);
        }

        mm->total -= mm->num_per_block;

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "free semaphore block: %p", block);

        ngx_free(block);
    }
}