#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  rrdvar_root_index; } ;
struct TYPE_9__ {TYPE_1__* rrdfamily; int /*<<< orphan*/  rrdvar_root_index; TYPE_4__* rrdhost; } ;
struct TYPE_8__ {int /*<<< orphan*/ * key_fullname; int /*<<< orphan*/ * key_fullid; int /*<<< orphan*/ * var_host_name; int /*<<< orphan*/ * var_host; int /*<<< orphan*/ * var_family_name; int /*<<< orphan*/ * var_family; int /*<<< orphan*/ * var_local; TYPE_3__* rrdset; } ;
struct TYPE_7__ {int /*<<< orphan*/  rrdvar_root_index; } ;
typedef  TYPE_2__ RRDSETVAR ;
typedef  TYPE_3__ RRDSET ;
typedef  TYPE_4__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdvar_free (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rrdsetvar_free_variables(RRDSETVAR *rs) {
    RRDSET *st = rs->rrdset;
    RRDHOST *host = st->rrdhost;

    // ------------------------------------------------------------------------
    // CHART
    rrdvar_free(host, &st->rrdvar_root_index, rs->var_local);
    rs->var_local = NULL;

    // ------------------------------------------------------------------------
    // FAMILY
    rrdvar_free(host, &st->rrdfamily->rrdvar_root_index, rs->var_family);
    rs->var_family = NULL;

    rrdvar_free(host, &st->rrdfamily->rrdvar_root_index, rs->var_family_name);
    rs->var_family_name = NULL;

    // ------------------------------------------------------------------------
    // HOST
    rrdvar_free(host, &host->rrdvar_root_index, rs->var_host);
    rs->var_host = NULL;

    rrdvar_free(host, &host->rrdvar_root_index, rs->var_host_name);
    rs->var_host_name = NULL;

    // ------------------------------------------------------------------------
    // KEYS
    freez(rs->key_fullid);
    rs->key_fullid = NULL;

    freez(rs->key_fullname);
    rs->key_fullname = NULL;
}