#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void ngx_google_perftools_conf_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *
ngx_google_perftools_create_conf(ngx_cycle_t *cycle)
{
    ngx_google_perftools_conf_t  *gptcf;

    gptcf = ngx_pcalloc(cycle->pool, sizeof(ngx_google_perftools_conf_t));
    if (gptcf == NULL) {
        return NULL;
    }

    /*
     * set by ngx_pcalloc()
     *
     *     gptcf->profiles = { 0, NULL };
     */

    return gptcf;
}