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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_2__ {char** errs; size_t type; int /*<<< orphan*/  pos; int /*<<< orphan*/  ts; } ;
struct tracing_log_err {TYPE_1__ info; int /*<<< orphan*/  cmd; int /*<<< orphan*/  loc; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  tracing_err_log_show_pos (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tracing_err_log_seq_show(struct seq_file *m, void *v)
{
	struct tracing_log_err *err = v;

	if (err) {
		const char *err_text = err->info.errs[err->info.type];
		u64 sec = err->info.ts;
		u32 nsec;

		nsec = do_div(sec, NSEC_PER_SEC);
		seq_printf(m, "[%5llu.%06u] %s%s", sec, nsec / 1000,
			   err->loc, err_text);
		seq_printf(m, "%s", err->cmd);
		tracing_err_log_show_pos(m, err->info.pos);
	}

	return 0;
}