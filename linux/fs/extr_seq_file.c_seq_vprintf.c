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
typedef  int /*<<< orphan*/  va_list ;
struct seq_file {scalar_t__ count; scalar_t__ size; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_set_overflow (struct seq_file*) ; 
 int vsnprintf (scalar_t__,scalar_t__,char const*,int /*<<< orphan*/ ) ; 

void seq_vprintf(struct seq_file *m, const char *f, va_list args)
{
	int len;

	if (m->count < m->size) {
		len = vsnprintf(m->buf + m->count, m->size - m->count, f, args);
		if (m->count + len < m->size) {
			m->count += len;
			return;
		}
	}
	seq_set_overflow(m);
}