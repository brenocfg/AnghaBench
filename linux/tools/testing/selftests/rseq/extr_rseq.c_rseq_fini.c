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
 scalar_t__ __rseq_handled ; 
 scalar_t__ rseq_ownership ; 

void __attribute__((destructor)) rseq_fini(void)
{
	if (!rseq_ownership)
		return;
	__rseq_handled = 0;
	rseq_ownership = 0;
}