#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* buf_ptr; int* buf_end; int fd; int* buffer; } ;
typedef  TYPE_1__ BufferedFile ;

/* Variables and functions */
 int CH_EOB ; 
 int CH_EOF ; 
 int IO_BUF_SIZE ; 
 int read (int,int*,int) ; 
 int total_bytes ; 

__attribute__((used)) static int tcc_peekc_slow(BufferedFile *bf)
{
	int len;
	/* only tries to read if really end of buffer */
	if (bf->buf_ptr >= bf->buf_end) {
		if (bf->fd != -1) {
#if defined(PARSE_DEBUG)
			len = 8;
#else
			len = IO_BUF_SIZE;
#endif
			len = read (bf->fd, bf->buffer, len);
			if (len < 0) {
				len = 0;
			}
		} else {
			len = 0;
		}
		total_bytes += len;
		bf->buf_ptr = bf->buffer;
		bf->buf_end = bf->buffer + len;
		*bf->buf_end = CH_EOB;
	}
	if (bf->buf_ptr < bf->buf_end) {
		return bf->buf_ptr[0];
	} else {
		bf->buf_ptr = bf->buf_end;
		return CH_EOF;
	}
}