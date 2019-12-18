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
struct TYPE_7__ {TYPE_1__* variables; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_2__* rrdset; int /*<<< orphan*/  options; void* value; int /*<<< orphan*/  type; int /*<<< orphan*/  variable; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  RRDVAR_TYPE ;
typedef  int /*<<< orphan*/  RRDVAR_OPTIONS ;
typedef  TYPE_1__ RRDSETVAR ;
typedef  TYPE_2__ RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  D_VARIABLES ; 
 scalar_t__ callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rrdsetvar_create_variables (TYPE_1__*) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdupz (char const*) ; 

RRDSETVAR *rrdsetvar_create(RRDSET *st, const char *variable, RRDVAR_TYPE type, void *value, RRDVAR_OPTIONS options) {
    debug(D_VARIABLES, "RRDVARSET create for chart id '%s' name '%s' with variable name '%s'", st->id, st->name, variable);
    RRDSETVAR *rs = (RRDSETVAR *)callocz(1, sizeof(RRDSETVAR));

    rs->variable = strdupz(variable);
    rs->hash = simple_hash(rs->variable);
    rs->type = type;
    rs->value = value;
    rs->options = options;
    rs->rrdset = st;

    rs->next = st->variables;
    st->variables = rs;

    rrdsetvar_create_variables(rs);

    return rs;
}