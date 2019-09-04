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
typedef  size_t u16 ;
struct isci_host {int tci_tail; size_t* tci_pool; } ;

/* Variables and functions */
 int SCI_MAX_IO_REQUESTS ; 

void isci_tci_free(struct isci_host *ihost, u16 tci)
{
	u16 tail = ihost->tci_tail & (SCI_MAX_IO_REQUESTS-1);

	ihost->tci_pool[tail] = tci;
	ihost->tci_tail = tail + 1;
}