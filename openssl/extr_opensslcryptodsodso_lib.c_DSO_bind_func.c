#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* meth; } ;
struct TYPE_5__ {int /*<<< orphan*/ * (* dso_bind_func ) (TYPE_2__*,char const*) ;} ;
typedef  int /*<<< orphan*/ * DSO_FUNC_TYPE ;
typedef  TYPE_2__ DSO ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_F_DSO_BIND_FUNC ; 
 int /*<<< orphan*/  DSO_R_SYM_FAILURE ; 
 int /*<<< orphan*/  DSO_R_UNSUPPORTED ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,char const*) ; 

DSO_FUNC_TYPE DSO_bind_func(DSO *dso, const char *symname)
{
    DSO_FUNC_TYPE ret = NULL;

    if ((dso == NULL) || (symname == NULL)) {
        DSOerr(DSO_F_DSO_BIND_FUNC, ERR_R_PASSED_NULL_PARAMETER);
        return NULL;
    }
    if (dso->meth->dso_bind_func == NULL) {
        DSOerr(DSO_F_DSO_BIND_FUNC, DSO_R_UNSUPPORTED);
        return NULL;
    }
    if ((ret = dso->meth->dso_bind_func(dso, symname)) == NULL) {
        DSOerr(DSO_F_DSO_BIND_FUNC, DSO_R_SYM_FAILURE);
        return NULL;
    }
    /* Success */
    return ret;
}