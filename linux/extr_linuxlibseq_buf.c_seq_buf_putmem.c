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
struct seq_buf {scalar_t__ size; scalar_t__ len; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,unsigned int) ; 
 scalar_t__ seq_buf_can_fit (struct seq_buf*,unsigned int) ; 
 int /*<<< orphan*/  seq_buf_set_overflow (struct seq_buf*) ; 

int seq_buf_putmem(struct seq_buf *s, const void *mem, unsigned int len)
{
	WARN_ON(s->size == 0);

	if (seq_buf_can_fit(s, len)) {
		memcpy(s->buffer + s->len, mem, len);
		s->len += len;
		return 0;
	}
	seq_buf_set_overflow(s);
	return -1;
}