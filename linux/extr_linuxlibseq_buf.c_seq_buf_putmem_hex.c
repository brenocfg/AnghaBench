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
struct seq_buf {scalar_t__ size; } ;

/* Variables and functions */
 int HEX_CHARS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 unsigned char hex_asc_hi (unsigned char const) ; 
 unsigned char hex_asc_lo (unsigned char const) ; 
 unsigned int min (unsigned int,int) ; 
 scalar_t__ seq_buf_has_overflowed (struct seq_buf*) ; 
 int /*<<< orphan*/  seq_buf_putmem (struct seq_buf*,unsigned char*,int) ; 

int seq_buf_putmem_hex(struct seq_buf *s, const void *mem,
		       unsigned int len)
{
	unsigned char hex[HEX_CHARS];
	const unsigned char *data = mem;
	unsigned int start_len;
	int i, j;

	WARN_ON(s->size == 0);

	while (len) {
		start_len = min(len, HEX_CHARS - 1);
#ifdef __BIG_ENDIAN
		for (i = 0, j = 0; i < start_len; i++) {
#else
		for (i = start_len-1, j = 0; i >= 0; i--) {
#endif
			hex[j++] = hex_asc_hi(data[i]);
			hex[j++] = hex_asc_lo(data[i]);
		}
		if (WARN_ON_ONCE(j == 0 || j/2 > len))
			break;

		/* j increments twice per loop */
		len -= j / 2;
		hex[j++] = ' ';

		seq_buf_putmem(s, hex, j);
		if (seq_buf_has_overflowed(s))
			return -1;
	}
	return 0;
}