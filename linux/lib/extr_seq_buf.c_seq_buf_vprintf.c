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
struct seq_buf {scalar_t__ size; scalar_t__ len; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  seq_buf_set_overflow (struct seq_buf*) ; 
 int vsnprintf (scalar_t__,scalar_t__,char const*,int /*<<< orphan*/ ) ; 

int seq_buf_vprintf(struct seq_buf *s, const char *fmt, va_list args)
{
	int len;

	WARN_ON(s->size == 0);

	if (s->len < s->size) {
		len = vsnprintf(s->buffer + s->len, s->size - s->len, fmt, args);
		if (s->len + len < s->size) {
			s->len += len;
			return 0;
		}
	}
	seq_buf_set_overflow(s);
	return -1;
}