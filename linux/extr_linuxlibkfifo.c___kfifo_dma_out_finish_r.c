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
struct __kfifo {unsigned int out; } ;

/* Variables and functions */
 unsigned int __kfifo_peek_n (struct __kfifo*,size_t) ; 

void __kfifo_dma_out_finish_r(struct __kfifo *fifo, size_t recsize)
{
	unsigned int len;

	len = __kfifo_peek_n(fifo, recsize);
	fifo->out += len + recsize;
}