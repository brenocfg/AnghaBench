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
struct seq_file {struct ddebug_iter* private; } ;
struct ddebug_iter {TYPE_1__* table; } ;
struct _ddebug {int /*<<< orphan*/  format; int /*<<< orphan*/  function; int /*<<< orphan*/  lineno; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  flagsbuf ;
struct TYPE_2__ {int /*<<< orphan*/  mod_name; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  ddebug_describe_flags (struct _ddebug*,char*,int) ; 
 int /*<<< orphan*/  seq_escape (struct seq_file*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  trim_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpr_info (char*,struct seq_file*,void*) ; 

__attribute__((used)) static int ddebug_proc_show(struct seq_file *m, void *p)
{
	struct ddebug_iter *iter = m->private;
	struct _ddebug *dp = p;
	char flagsbuf[10];

	vpr_info("called m=%p p=%p\n", m, p);

	if (p == SEQ_START_TOKEN) {
		seq_puts(m,
			 "# filename:lineno [module]function flags format\n");
		return 0;
	}

	seq_printf(m, "%s:%u [%s]%s =%s \"",
		   trim_prefix(dp->filename), dp->lineno,
		   iter->table->mod_name, dp->function,
		   ddebug_describe_flags(dp, flagsbuf, sizeof(flagsbuf)));
	seq_escape(m, dp->format, "\t\r\n\"");
	seq_puts(m, "\"\n");

	return 0;
}