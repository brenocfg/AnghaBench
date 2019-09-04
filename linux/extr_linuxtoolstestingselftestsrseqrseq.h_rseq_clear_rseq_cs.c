#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ptr; } ;
struct TYPE_4__ {TYPE_1__ rseq_cs; } ;

/* Variables and functions */
 TYPE_2__ __rseq_abi ; 

__attribute__((used)) static inline void rseq_clear_rseq_cs(void)
{
#ifdef __LP64__
	__rseq_abi.rseq_cs.ptr = 0;
#else
	__rseq_abi.rseq_cs.ptr.ptr32 = 0;
#endif
}