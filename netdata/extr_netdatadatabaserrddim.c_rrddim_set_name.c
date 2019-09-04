#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ exposed; int /*<<< orphan*/  name; int /*<<< orphan*/  hash_name; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  config_section; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RRDSET ;
typedef  TYPE_2__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MAX_NAME ; 
 int /*<<< orphan*/  D_RRD_CALLS ; 
 int /*<<< orphan*/  RRDSET_FLAG_UPSTREAM_EXPOSED ; 
 int /*<<< orphan*/  config_set_default (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rrddimvar_rename_all (TYPE_2__*) ; 
 int /*<<< orphan*/  rrdset_flag_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ unlikely (int) ; 

inline int rrddim_set_name(RRDSET *st, RRDDIM *rd, const char *name) {
    if(unlikely(!name || !*name || !strcmp(rd->name, name)))
        return 0;

    debug(D_RRD_CALLS, "rrddim_set_name() from %s.%s to %s.%s", st->name, rd->name, st->name, name);

    char varname[CONFIG_MAX_NAME + 1];
    snprintfz(varname, CONFIG_MAX_NAME, "dim %s name", rd->id);
    rd->name = config_set_default(st->config_section, varname, name);
    rd->hash_name = simple_hash(rd->name);
    rrddimvar_rename_all(rd);
    rd->exposed = 0;
    rrdset_flag_clear(st, RRDSET_FLAG_UPSTREAM_EXPOSED);
    return 1;
}