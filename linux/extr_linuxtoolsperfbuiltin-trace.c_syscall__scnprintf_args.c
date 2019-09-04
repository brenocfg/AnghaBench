#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct trace {int dummy; } ;
struct thread_trace {int /*<<< orphan*/ * ret_scnprintf; } ;
struct thread {int dummy; } ;
struct syscall_arg {unsigned char* args; size_t idx; int mask; struct thread* thread; struct trace* trace; } ;
struct syscall {size_t nr_args; int /*<<< orphan*/  tp_format; TYPE_1__* arg_fmt; struct format_field* args; } ;
struct format_field {int /*<<< orphan*/  name; struct format_field* next; } ;
struct TYPE_2__ {scalar_t__ scnprintf; scalar_t__ parm; scalar_t__ show_zero; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SCA_STRARRAY ; 
 scalar_t__ SCA_STRARRAYS ; 
 scalar_t__ scnprintf (char*,size_t,char*,...) ; 
 scalar_t__ syscall__scnprintf_name (struct syscall*,char*,size_t,struct syscall_arg*) ; 
 scalar_t__ syscall__scnprintf_val (struct syscall*,char*,size_t,struct syscall_arg*,unsigned long) ; 
 unsigned long syscall_arg__val (struct syscall_arg*,size_t) ; 
 struct thread_trace* thread__priv (struct thread*) ; 

__attribute__((used)) static size_t syscall__scnprintf_args(struct syscall *sc, char *bf, size_t size,
				      unsigned char *args, struct trace *trace,
				      struct thread *thread)
{
	size_t printed = 0;
	unsigned long val;
	u8 bit = 1;
	struct syscall_arg arg = {
		.args	= args,
		.idx	= 0,
		.mask	= 0,
		.trace  = trace,
		.thread = thread,
	};
	struct thread_trace *ttrace = thread__priv(thread);

	/*
	 * Things like fcntl will set this in its 'cmd' formatter to pick the
	 * right formatter for the return value (an fd? file flags?), which is
	 * not needed for syscalls that always return a given type, say an fd.
	 */
	ttrace->ret_scnprintf = NULL;

	if (sc->args != NULL) {
		struct format_field *field;

		for (field = sc->args; field;
		     field = field->next, ++arg.idx, bit <<= 1) {
			if (arg.mask & bit)
				continue;

			val = syscall_arg__val(&arg, arg.idx);

			/*
 			 * Suppress this argument if its value is zero and
 			 * and we don't have a string associated in an
 			 * strarray for it.
 			 */
			if (val == 0 &&
			    !(sc->arg_fmt &&
			      (sc->arg_fmt[arg.idx].show_zero ||
			       sc->arg_fmt[arg.idx].scnprintf == SCA_STRARRAY ||
			       sc->arg_fmt[arg.idx].scnprintf == SCA_STRARRAYS) &&
			      sc->arg_fmt[arg.idx].parm))
				continue;

			printed += scnprintf(bf + printed, size - printed,
					     "%s%s: ", printed ? ", " : "", field->name);
			printed += syscall__scnprintf_val(sc, bf + printed, size - printed, &arg, val);
		}
	} else if (IS_ERR(sc->tp_format)) {
		/*
		 * If we managed to read the tracepoint /format file, then we
		 * may end up not having any args, like with gettid(), so only
		 * print the raw args when we didn't manage to read it.
		 */
		while (arg.idx < sc->nr_args) {
			if (arg.mask & bit)
				goto next_arg;
			val = syscall_arg__val(&arg, arg.idx);
			if (printed)
				printed += scnprintf(bf + printed, size - printed, ", ");
			printed += syscall__scnprintf_name(sc, bf + printed, size - printed, &arg);
			printed += syscall__scnprintf_val(sc, bf + printed, size - printed, &arg, val);
next_arg:
			++arg.idx;
			bit <<= 1;
		}
	}

	return printed;
}