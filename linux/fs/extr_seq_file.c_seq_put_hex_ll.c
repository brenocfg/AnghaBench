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
typedef  int /*<<< orphan*/  v ;
struct seq_file {unsigned int count; unsigned int size; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int __builtin_clzll (unsigned long long) ; 
 int /*<<< orphan*/ * hex_asc ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char const) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char const*) ; 
 int /*<<< orphan*/  seq_set_overflow (struct seq_file*) ; 

void seq_put_hex_ll(struct seq_file *m, const char *delimiter,
				unsigned long long v, unsigned int width)
{
	unsigned int len;
	int i;

	if (delimiter && delimiter[0]) {
		if (delimiter[1] == 0)
			seq_putc(m, delimiter[0]);
		else
			seq_puts(m, delimiter);
	}

	/* If x is 0, the result of __builtin_clzll is undefined */
	if (v == 0)
		len = 1;
	else
		len = (sizeof(v) * 8 - __builtin_clzll(v) + 3) / 4;

	if (len < width)
		len = width;

	if (m->count + len > m->size) {
		seq_set_overflow(m);
		return;
	}

	for (i = len - 1; i >= 0; i--) {
		m->buf[m->count + i] = hex_asc[0xf & v];
		v = v >> 4;
	}
	m->count += len;
}