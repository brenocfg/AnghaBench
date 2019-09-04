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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int RBUF_LEN ; 
 char* rbuf ; 
 int rbuf_len ; 
 int rbuf_start ; 

__attribute__((used)) static int isoc_read_data (char *page, char **start,
			   off_t off, int count,
			   int *eof, void *data)
{
	int i;
	static int c = 0;
	static int done = 0;
	static int s = 0;

/*
	printk ("\ncount: %d\n", count);
	printk ("rbuf_start: %d\n", rbuf_start);
	printk ("rbuf_len: %d\n", rbuf_len);
	printk ("off: %d\n", off);
	printk ("start: %p\n\n", *start);
*/
	if (done) {
		c = 0;
		done = 0;
		*eof = 1;
		return 0;
	}

	if (c == 0) {
		if (rbuf_len == RBUF_LEN)
			s = rbuf_start;
		else s = 0;
	}

	for (i=0; i<count && c<rbuf_len; i++, c++) {
		page[i] = rbuf[(c+s) % RBUF_LEN];
	}
	*start = page;

	if (c >= rbuf_len) {
		*eof = 1;
		done = 1;
	}


	return i;
}