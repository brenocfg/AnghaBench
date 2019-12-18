#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (char*) ; 
 int security_sid_to_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  seq_escape (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static int show_sid(struct seq_file *m, u32 sid)
{
	char *context = NULL;
	u32 len;
	int rc;

	rc = security_sid_to_context(&selinux_state, sid,
					     &context, &len);
	if (!rc) {
		bool has_comma = context && strchr(context, ',');

		seq_putc(m, '=');
		if (has_comma)
			seq_putc(m, '\"');
		seq_escape(m, context, "\"\n\\");
		if (has_comma)
			seq_putc(m, '\"');
	}
	kfree(context);
	return rc;
}