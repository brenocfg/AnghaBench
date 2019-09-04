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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_event_process_posted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_init_queue ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_stat_init_process(ngx_cycle_t *cycle)
{
    /*
     * HTTP process initializer is called
     * after event module initializer
     * so we can run posted events here
     */

    ngx_event_process_posted(cycle, &ngx_rtmp_init_queue);

    return NGX_OK;
}