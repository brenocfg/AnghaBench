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
 int __rseq_handled ; 
 int rseq_ownership ; 

void __attribute__((constructor)) rseq_init(void)
{
	/* Check whether rseq is handled by another library. */
	if (__rseq_handled)
		return;
	__rseq_handled = 1;
	rseq_ownership = 1;
}