#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* value; struct TYPE_7__* name; TYPE_1__* pmod; } ;
struct TYPE_6__ {int /*<<< orphan*/  links; int /*<<< orphan*/  (* finish ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ CONF_IMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void module_finish(CONF_IMODULE *imod)
{
    if (!imod)
        return;
    if (imod->pmod->finish)
        imod->pmod->finish(imod);
    imod->pmod->links--;
    OPENSSL_free(imod->name);
    OPENSSL_free(imod->value);
    OPENSSL_free(imod);
}