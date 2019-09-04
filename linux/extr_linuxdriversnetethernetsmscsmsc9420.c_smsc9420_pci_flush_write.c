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
struct smsc9420_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID_REV ; 
 int /*<<< orphan*/  smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smsc9420_pci_flush_write(struct smsc9420_pdata *pd)
{
	/* to ensure PCI write completion, we must perform a PCI read */
	smsc9420_reg_read(pd, ID_REV);
}