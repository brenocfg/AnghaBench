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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  perl; } ;
typedef  TYPE_1__ ngx_http_perl_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
typedef  int /*<<< orphan*/  I32 ;

/* Variables and functions */
 int /*<<< orphan*/  GvSV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  PERL_SET_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERL_SET_INTERP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVt_PV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dTHXa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_fetchpv (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_cycle_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_perl_module ; 
 scalar_t__ ngx_pid ; 
 int /*<<< orphan*/  sv_setiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_perl_init_worker(ngx_cycle_t *cycle)
{
    ngx_http_perl_main_conf_t  *pmcf;

    pmcf = ngx_http_cycle_get_module_main_conf(cycle, ngx_http_perl_module);

    if (pmcf) {
        dTHXa(pmcf->perl);
        PERL_SET_CONTEXT(pmcf->perl);
        PERL_SET_INTERP(pmcf->perl);

        /* set worker's $$ */

        sv_setiv(GvSV(gv_fetchpv("$", TRUE, SVt_PV)), (I32) ngx_pid);
    }

    return NGX_OK;
}