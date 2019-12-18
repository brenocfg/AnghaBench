#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tp_name ;
struct TYPE_10__ {int /*<<< orphan*/ * table; } ;
struct trace {TYPE_2__ syscalls; TYPE_5__* sctbl; } ;
struct syscall {int nonexistent; char const* name; int is_exit; int is_open; int /*<<< orphan*/  nr_args; TYPE_4__* args; TYPE_7__* tp_format; TYPE_6__* fmt; } ;
struct TYPE_11__ {int nr_fields; TYPE_4__* fields; } ;
struct TYPE_15__ {TYPE_3__ format; } ;
struct TYPE_14__ {char const* alias; } ;
struct TYPE_9__ {scalar_t__ max_id; } ;
struct TYPE_13__ {TYPE_1__ syscalls; } ;
struct TYPE_12__ {char const* name; struct TYPE_12__* next; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (TYPE_7__*) ; 
 int PTR_ERR (TYPE_7__*) ; 
 int /*<<< orphan*/ * calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ syscall__alloc_arg_fmts (struct syscall*,int) ; 
 int syscall__set_arg_fmts (struct syscall*) ; 
 TYPE_6__* syscall_fmt__find (char const*) ; 
 char* syscalltbl__name (TYPE_5__*,int) ; 
 void* trace_event__tp_format (char*,char*) ; 

__attribute__((used)) static int trace__read_syscall_info(struct trace *trace, int id)
{
	char tp_name[128];
	struct syscall *sc;
	const char *name = syscalltbl__name(trace->sctbl, id);

	if (trace->syscalls.table == NULL) {
		trace->syscalls.table = calloc(trace->sctbl->syscalls.max_id + 1, sizeof(*sc));
		if (trace->syscalls.table == NULL)
			return -ENOMEM;
	}

	sc = trace->syscalls.table + id;
	if (sc->nonexistent)
		return 0;

	if (name == NULL) {
		sc->nonexistent = true;
		return 0;
	}

	sc->name = name;
	sc->fmt  = syscall_fmt__find(sc->name);

	snprintf(tp_name, sizeof(tp_name), "sys_enter_%s", sc->name);
	sc->tp_format = trace_event__tp_format("syscalls", tp_name);

	if (IS_ERR(sc->tp_format) && sc->fmt && sc->fmt->alias) {
		snprintf(tp_name, sizeof(tp_name), "sys_enter_%s", sc->fmt->alias);
		sc->tp_format = trace_event__tp_format("syscalls", tp_name);
	}

	if (syscall__alloc_arg_fmts(sc, IS_ERR(sc->tp_format) ? 6 : sc->tp_format->format.nr_fields))
		return -ENOMEM;

	if (IS_ERR(sc->tp_format))
		return PTR_ERR(sc->tp_format);

	sc->args = sc->tp_format->format.fields;
	/*
	 * We need to check and discard the first variable '__syscall_nr'
	 * or 'nr' that mean the syscall number. It is needless here.
	 * So drop '__syscall_nr' or 'nr' field but does not exist on older kernels.
	 */
	if (sc->args && (!strcmp(sc->args->name, "__syscall_nr") || !strcmp(sc->args->name, "nr"))) {
		sc->args = sc->args->next;
		--sc->nr_args;
	}

	sc->is_exit = !strcmp(name, "exit_group") || !strcmp(name, "exit");
	sc->is_open = !strcmp(name, "open") || !strcmp(name, "openat");

	return syscall__set_arg_fmts(sc);
}