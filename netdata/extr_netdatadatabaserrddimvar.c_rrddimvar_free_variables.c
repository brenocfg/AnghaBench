#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* rrdset; } ;
struct TYPE_11__ {int /*<<< orphan*/ * key_fullnamename; int /*<<< orphan*/ * key_fullnameid; int /*<<< orphan*/ * key_contextname; int /*<<< orphan*/ * key_contextid; int /*<<< orphan*/ * key_fullidname; int /*<<< orphan*/ * key_fullidid; int /*<<< orphan*/ * key_name; int /*<<< orphan*/ * key_id; int /*<<< orphan*/ * var_host_chartnamename; int /*<<< orphan*/ * var_host_chartnameid; int /*<<< orphan*/ * var_host_chartidname; int /*<<< orphan*/ * var_host_chartidid; int /*<<< orphan*/ * var_family_contextname; int /*<<< orphan*/ * var_family_contextid; int /*<<< orphan*/ * var_family_name; int /*<<< orphan*/ * var_family_id; int /*<<< orphan*/ * var_local_name; int /*<<< orphan*/ * var_local_id; TYPE_5__* rrddim; } ;
struct TYPE_10__ {int /*<<< orphan*/  rrdvar_root_index; } ;
struct TYPE_9__ {TYPE_1__* rrdfamily; int /*<<< orphan*/  rrdvar_root_index; TYPE_3__* rrdhost; } ;
struct TYPE_8__ {int /*<<< orphan*/  rrdvar_root_index; } ;
typedef  TYPE_2__ RRDSET ;
typedef  TYPE_3__ RRDHOST ;
typedef  TYPE_4__ RRDDIMVAR ;
typedef  TYPE_5__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdvar_free (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rrddimvar_free_variables(RRDDIMVAR *rs) {
    RRDDIM *rd = rs->rrddim;
    RRDSET *st = rd->rrdset;
    RRDHOST *host = st->rrdhost;

    // CHART VARIABLES FOR THIS DIMENSION

    rrdvar_free(host, &st->rrdvar_root_index, rs->var_local_id);
    rs->var_local_id = NULL;

    rrdvar_free(host, &st->rrdvar_root_index, rs->var_local_name);
    rs->var_local_name = NULL;

    // FAMILY VARIABLES FOR THIS DIMENSION

    rrdvar_free(host, &st->rrdfamily->rrdvar_root_index, rs->var_family_id);
    rs->var_family_id = NULL;

    rrdvar_free(host, &st->rrdfamily->rrdvar_root_index, rs->var_family_name);
    rs->var_family_name = NULL;

    rrdvar_free(host, &st->rrdfamily->rrdvar_root_index, rs->var_family_contextid);
    rs->var_family_contextid = NULL;

    rrdvar_free(host, &st->rrdfamily->rrdvar_root_index, rs->var_family_contextname);
    rs->var_family_contextname = NULL;

    // HOST VARIABLES FOR THIS DIMENSION

    rrdvar_free(host, &host->rrdvar_root_index, rs->var_host_chartidid);
    rs->var_host_chartidid = NULL;

    rrdvar_free(host, &host->rrdvar_root_index, rs->var_host_chartidname);
    rs->var_host_chartidname = NULL;

    rrdvar_free(host, &host->rrdvar_root_index, rs->var_host_chartnameid);
    rs->var_host_chartnameid = NULL;

    rrdvar_free(host, &host->rrdvar_root_index, rs->var_host_chartnamename);
    rs->var_host_chartnamename = NULL;

    // KEYS

    freez(rs->key_id);
    rs->key_id = NULL;

    freez(rs->key_name);
    rs->key_name = NULL;

    freez(rs->key_fullidid);
    rs->key_fullidid = NULL;

    freez(rs->key_fullidname);
    rs->key_fullidname = NULL;

    freez(rs->key_contextid);
    rs->key_contextid = NULL;

    freez(rs->key_contextname);
    rs->key_contextname = NULL;

    freez(rs->key_fullnameid);
    rs->key_fullnameid = NULL;

    freez(rs->key_fullnamename);
    rs->key_fullnamename = NULL;
}