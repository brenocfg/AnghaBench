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
struct scatterlist {int dummy; } ;
struct __kfifo {int /*<<< orphan*/  in; } ;

/* Variables and functions */
 unsigned int kfifo_unused (struct __kfifo*) ; 
 unsigned int setup_sgl (struct __kfifo*,struct scatterlist*,int,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int __kfifo_dma_in_prepare(struct __kfifo *fifo,
		struct scatterlist *sgl, int nents, unsigned int len)
{
	unsigned int l;

	l = kfifo_unused(fifo);
	if (len > l)
		len = l;

	return setup_sgl(fifo, sgl, nents, len, fifo->in);
}