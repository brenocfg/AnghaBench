#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct ima_template_entry {char* pcr; TYPE_3__* template_data; TYPE_2__* template_desc; int /*<<< orphan*/  digest; } ;
struct ima_queue_entry {struct ima_template_entry* entry; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {char* name; char* fmt; int num_fields; TYPE_1__** fields; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* field_show ) (struct seq_file*,int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IMA_SHOW_ASCII ; 
 int /*<<< orphan*/  TPM_DIGEST_SIZE ; 
 int /*<<< orphan*/  ima_print_digest (struct seq_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct seq_file*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int ima_ascii_measurements_show(struct seq_file *m, void *v)
{
	/* the list never shrinks, so we don't need a lock here */
	struct ima_queue_entry *qe = v;
	struct ima_template_entry *e;
	char *template_name;
	int i;

	/* get entry */
	e = qe->entry;
	if (e == NULL)
		return -1;

	template_name = (e->template_desc->name[0] != '\0') ?
	    e->template_desc->name : e->template_desc->fmt;

	/* 1st: PCR used (config option) */
	seq_printf(m, "%2d ", e->pcr);

	/* 2nd: SHA1 template hash */
	ima_print_digest(m, e->digest, TPM_DIGEST_SIZE);

	/* 3th:  template name */
	seq_printf(m, " %s", template_name);

	/* 4th:  template specific data */
	for (i = 0; i < e->template_desc->num_fields; i++) {
		seq_puts(m, " ");
		if (e->template_data[i].len == 0)
			continue;

		e->template_desc->fields[i]->field_show(m, IMA_SHOW_ASCII,
							&e->template_data[i]);
	}
	seq_puts(m, "\n");
	return 0;
}