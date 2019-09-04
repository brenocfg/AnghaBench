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
struct seq_buf {scalar_t__ size; unsigned char* buffer; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ seq_buf_can_fit (struct seq_buf*,int) ; 
 int /*<<< orphan*/  seq_buf_set_overflow (struct seq_buf*) ; 

int seq_buf_putc(struct seq_buf *s, unsigned char c)
{
	WARN_ON(s->size == 0);

	if (seq_buf_can_fit(s, 1)) {
		s->buffer[s->len++] = c;
		return 0;
	}
	seq_buf_set_overflow(s);
	return -1;
}