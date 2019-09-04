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
struct rpcrdma_regbuf {struct ib_device* rg_device; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ib_device *
rdmab_device(struct rpcrdma_regbuf *rb)
{
	return rb->rg_device;
}