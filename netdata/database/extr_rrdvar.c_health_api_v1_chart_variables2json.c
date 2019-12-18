#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct variable2json_helper {scalar_t__ counter; int /*<<< orphan*/  options; int /*<<< orphan*/ * buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  rrdvar_root_index; int /*<<< orphan*/  hostname; } ;
struct TYPE_6__ {TYPE_1__* rrdfamily; int /*<<< orphan*/  family; int /*<<< orphan*/  rrdvar_root_index; int /*<<< orphan*/  context; int /*<<< orphan*/  name; int /*<<< orphan*/  id; TYPE_3__* rrdhost; } ;
struct TYPE_5__ {int /*<<< orphan*/  rrdvar_root_index; } ;
typedef  TYPE_2__ RRDSET ;
typedef  TYPE_3__ RRDHOST ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  RRDVAR_OPTION_DEFAULT ; 
 int /*<<< orphan*/  avl_traverse_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  single_variable2json ; 

void health_api_v1_chart_variables2json(RRDSET *st, BUFFER *buf) {
    RRDHOST *host = st->rrdhost;

    struct variable2json_helper helper = {
            .buf = buf,
            .counter = 0,
            .options = RRDVAR_OPTION_DEFAULT
    };

    buffer_sprintf(buf, "{\n\t\"chart\": \"%s\",\n\t\"chart_name\": \"%s\",\n\t\"chart_context\": \"%s\",\n\t\"chart_variables\": {", st->id, st->name, st->context);
    avl_traverse_lock(&st->rrdvar_root_index, single_variable2json, (void *)&helper);
    buffer_sprintf(buf, "\n\t},\n\t\"family\": \"%s\",\n\t\"family_variables\": {", st->family);
    helper.counter = 0;
    avl_traverse_lock(&st->rrdfamily->rrdvar_root_index, single_variable2json, (void *)&helper);
    buffer_sprintf(buf, "\n\t},\n\t\"host\": \"%s\",\n\t\"host_variables\": {", host->hostname);
    helper.counter = 0;
    avl_traverse_lock(&host->rrdvar_root_index, single_variable2json, (void *)&helper);
    buffer_strcat(buf, "\n\t}\n}\n");
}