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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESCAPE_OCTAL ; 
 int /*<<< orphan*/  seq_commit (struct seq_file*,int) ; 
 size_t seq_get_buf (struct seq_file*,char**) ; 
 int string_escape_str (char const*,char*,size_t,int /*<<< orphan*/ ,char const*) ; 

void seq_escape(struct seq_file *m, const char *s, const char *esc)
{
	char *buf;
	size_t size = seq_get_buf(m, &buf);
	int ret;

	ret = string_escape_str(s, buf, size, ESCAPE_OCTAL, esc);
	seq_commit(m, ret < size ? ret : -1);
}