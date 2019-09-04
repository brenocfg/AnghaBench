#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct xdpsock {TYPE_1__* umem; } ;
struct TYPE_2__ {void* frames; } ;

/* Variables and functions */

__attribute__((used)) static inline void *xq_get_data(struct xdpsock *xsk, u64 addr)
{
	return &xsk->umem->frames[addr];
}