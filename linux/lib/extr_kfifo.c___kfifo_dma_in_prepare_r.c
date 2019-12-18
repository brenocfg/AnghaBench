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
struct __kfifo {scalar_t__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int __kfifo_max_r (unsigned int,size_t) ; 
 unsigned int kfifo_unused (struct __kfifo*) ; 
 unsigned int setup_sgl (struct __kfifo*,struct scatterlist*,int,unsigned int,scalar_t__) ; 

unsigned int __kfifo_dma_in_prepare_r(struct __kfifo *fifo,
	struct scatterlist *sgl, int nents, unsigned int len, size_t recsize)
{
	BUG_ON(!nents);

	len = __kfifo_max_r(len, recsize);

	if (len + recsize > kfifo_unused(fifo))
		return 0;

	return setup_sgl(fifo, sgl, nents, len, fifo->in + recsize);
}