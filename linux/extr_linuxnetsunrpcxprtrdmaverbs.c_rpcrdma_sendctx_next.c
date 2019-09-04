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
struct rpcrdma_buffer {unsigned long rb_sc_last; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned long rpcrdma_sendctx_next(struct rpcrdma_buffer *buf,
					  unsigned long item)
{
	return likely(item < buf->rb_sc_last) ? item + 1 : 0;
}