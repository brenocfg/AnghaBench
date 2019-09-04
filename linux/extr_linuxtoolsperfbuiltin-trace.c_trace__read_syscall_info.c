#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tp_name ;
struct TYPE_6__ {int max; struct syscall* table; } ;
struct trace {TYPE_1__ syscalls; int /*<<< orphan*/  sctbl; } ;
struct syscall {char const* name; int is_exit; int is_open; int /*<<< orphan*/  nr_args; TYPE_3__* args; TYPE_5__* tp_format; TYPE_4__* fmt; } ;
struct TYPE_7__ {int nr_fields; TYPE_3__* fields; } ;
struct TYPE_10__ {TYPE_2__ format; } ;
struct TYPE_9__ {char const* alias; } ;
struct TYPE_8__ {char const* name; struct TYPE_8__* next; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (struct syscall*,int /*<<< orphan*/ ,int) ; 
 struct syscall* realloc (struct syscall*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ syscall__alloc_arg_fmts (struct syscall*,int) ; 
 int syscall__set_arg_fmts (struct syscall*) ; 
 TYPE_4__* syscall_fmt__find (char const*) ; 
 char* syscalltbl__name (int /*<<< orphan*/ ,int) ; 
 void* trace_event__tp_format (char*,char*) ; 

__attribute__((used)) static int trace__read_syscall_info(struct trace *trace, int id)
{
	char tp_name[128];
	struct syscall *sc;
	const char *name = syscalltbl__name(trace->sctbl, id);

	if (name == NULL)
		return -1;

	if (id > trace->syscalls.max) {
		struct syscall *nsyscalls = realloc(trace->syscalls.table, (id + 1) * sizeof(*sc));

		if (nsyscalls == NULL)
			return -1;

		if (trace->syscalls.max != -1) {
			memset(nsyscalls + trace->syscalls.max + 1, 0,
			       (id - trace->syscalls.max) * sizeof(*sc));
		} else {
			memset(nsyscalls, 0, (id + 1) * sizeof(*sc));
		}

		trace->syscalls.table = nsyscalls;
		trace->syscalls.max   = id;
	}

	sc = trace->syscalls.table + id;
	sc->name = name;

	sc->fmt  = syscall_fmt__find(sc->name);

	snprintf(tp_name, sizeof(tp_name), "sys_enter_%s", sc->name);
	sc->tp_format = trace_event__tp_format("syscalls", tp_name);

	if (IS_ERR(sc->tp_format) && sc->fmt && sc->fmt->alias) {
		snprintf(tp_name, sizeof(tp_name), "sys_enter_%s", sc->fmt->alias);
		sc->tp_format = trace_event__tp_format("syscalls", tp_name);
	}

	if (syscall__alloc_arg_fmts(sc, IS_ERR(sc->tp_format) ? 6 : sc->tp_format->format.nr_fields))
		return -1;

	if (IS_ERR(sc->tp_format))
		return -1;

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