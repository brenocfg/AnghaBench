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
struct TYPE_12__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; TYPE_2__* rrdset; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type; void* key_fullnamename; void* var_host_chartnamename; void* key_fullnameid; void* var_host_chartnameid; void* key_fullidname; void* var_host_chartidname; void* key_fullidid; void* var_host_chartidid; void* key_contextname; void* var_family_contextname; void* key_contextid; void* var_family_contextid; void* key_name; void* var_family_name; void* key_id; void* var_family_id; void* var_local_name; void* var_local_id; int /*<<< orphan*/  suffix; int /*<<< orphan*/  prefix; TYPE_5__* rrddim; } ;
struct TYPE_10__ {int /*<<< orphan*/  rrdvar_root_index; } ;
struct TYPE_9__ {TYPE_1__* rrdfamily; int /*<<< orphan*/  rrdvar_root_index; int /*<<< orphan*/  name; int /*<<< orphan*/  context; int /*<<< orphan*/  id; TYPE_3__* rrdhost; } ;
struct TYPE_8__ {int /*<<< orphan*/  rrdvar_root_index; } ;
typedef  TYPE_2__ RRDSET ;
typedef  TYPE_3__ RRDHOST ;
typedef  TYPE_4__ RRDDIMVAR ;
typedef  TYPE_5__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  RRDDIMVAR_ID_MAX ; 
 int /*<<< orphan*/  RRDVAR_OPTION_DEFAULT ; 
 int /*<<< orphan*/  rrddimvar_free_variables (TYPE_4__*) ; 
 void* rrdvar_create_and_index (char*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,...) ; 
 void* strdupz (char*) ; 

__attribute__((used)) static inline void rrddimvar_create_variables(RRDDIMVAR *rs) {
    rrddimvar_free_variables(rs);

    RRDDIM *rd = rs->rrddim;
    RRDSET *st = rd->rrdset;
    RRDHOST *host = st->rrdhost;

    char buffer[RRDDIMVAR_ID_MAX + 1];

    // KEYS

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s%s%s", rs->prefix, rd->id, rs->suffix);
    rs->key_id = strdupz(buffer);

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s%s%s", rs->prefix, rd->name, rs->suffix);
    rs->key_name = strdupz(buffer);

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s.%s", st->id, rs->key_id);
    rs->key_fullidid = strdupz(buffer);

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s.%s", st->id, rs->key_name);
    rs->key_fullidname = strdupz(buffer);

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s.%s", st->context, rs->key_id);
    rs->key_contextid = strdupz(buffer);

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s.%s", st->context, rs->key_name);
    rs->key_contextname = strdupz(buffer);

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s.%s", st->name, rs->key_id);
    rs->key_fullnameid = strdupz(buffer);

    snprintfz(buffer, RRDDIMVAR_ID_MAX, "%s.%s", st->name, rs->key_name);
    rs->key_fullnamename = strdupz(buffer);

    // CHART VARIABLES FOR THIS DIMENSION
    // -----------------------------------
    //
    // dimensions are available as:
    // - $id
    // - $name

    rs->var_local_id           = rrdvar_create_and_index("local", &st->rrdvar_root_index, rs->key_id, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
    rs->var_local_name         = rrdvar_create_and_index("local", &st->rrdvar_root_index, rs->key_name, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);

    // FAMILY VARIABLES FOR THIS DIMENSION
    // -----------------------------------
    //
    // dimensions are available as:
    // - $id                 (only the first, when multiple overlap)
    // - $name               (only the first, when multiple overlap)
    // - $chart-context.id
    // - $chart-context.name

    rs->var_family_id          = rrdvar_create_and_index("family", &st->rrdfamily->rrdvar_root_index, rs->key_id, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
    rs->var_family_name        = rrdvar_create_and_index("family", &st->rrdfamily->rrdvar_root_index, rs->key_name, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
    rs->var_family_contextid   = rrdvar_create_and_index("family", &st->rrdfamily->rrdvar_root_index, rs->key_contextid, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
    rs->var_family_contextname = rrdvar_create_and_index("family", &st->rrdfamily->rrdvar_root_index, rs->key_contextname, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);

    // HOST VARIABLES FOR THIS DIMENSION
    // -----------------------------------
    //
    // dimensions are available as:
    // - $chart-id.id
    // - $chart-id.name
    // - $chart-name.id
    // - $chart-name.name

    rs->var_host_chartidid      = rrdvar_create_and_index("host", &host->rrdvar_root_index, rs->key_fullidid, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
    rs->var_host_chartidname    = rrdvar_create_and_index("host", &host->rrdvar_root_index, rs->key_fullidname, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
    rs->var_host_chartnameid    = rrdvar_create_and_index("host", &host->rrdvar_root_index, rs->key_fullnameid, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
    rs->var_host_chartnamename  = rrdvar_create_and_index("host", &host->rrdvar_root_index, rs->key_fullnamename, rs->type, RRDVAR_OPTION_DEFAULT, rs->value);
}