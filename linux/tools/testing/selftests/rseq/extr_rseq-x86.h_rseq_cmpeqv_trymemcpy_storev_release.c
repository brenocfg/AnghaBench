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

/* Variables and functions */
 int rseq_cmpeqv_trymemcpy_storev (intptr_t*,intptr_t,void*,void*,size_t,intptr_t,int) ; 

__attribute__((used)) static inline __attribute__((always_inline))
int rseq_cmpeqv_trymemcpy_storev_release(intptr_t *v, intptr_t expect,
					 void *dst, void *src, size_t len,
					 intptr_t newv, int cpu)
{
	return rseq_cmpeqv_trymemcpy_storev(v, expect, dst, src, len,
					    newv, cpu);
}