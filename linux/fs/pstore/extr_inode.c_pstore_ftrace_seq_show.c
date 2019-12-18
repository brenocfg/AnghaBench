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
struct seq_file {struct pstore_private* private; } ;
struct pstore_private {TYPE_1__* record; } ;
struct pstore_ftrace_seq_data {scalar_t__ off; } ;
struct pstore_ftrace_record {scalar_t__ parent_ip; scalar_t__ ip; } ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  pstore_ftrace_decode_cpu (struct pstore_ftrace_record*) ; 
 int /*<<< orphan*/  pstore_ftrace_read_timestamp (struct pstore_ftrace_record*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*,void*) ; 

__attribute__((used)) static int pstore_ftrace_seq_show(struct seq_file *s, void *v)
{
	struct pstore_private *ps = s->private;
	struct pstore_ftrace_seq_data *data = v;
	struct pstore_ftrace_record *rec;

	rec = (struct pstore_ftrace_record *)(ps->record->buf + data->off);

	seq_printf(s, "CPU:%d ts:%llu %08lx  %08lx  %ps <- %pS\n",
		   pstore_ftrace_decode_cpu(rec),
		   pstore_ftrace_read_timestamp(rec),
		   rec->ip, rec->parent_ip, (void *)rec->ip,
		   (void *)rec->parent_ip);

	return 0;
}