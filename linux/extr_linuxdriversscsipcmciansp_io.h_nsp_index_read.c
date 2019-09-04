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
 scalar_t__ DATAREG ; 
 scalar_t__ INDEXREG ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline unsigned char nsp_index_read(unsigned int BaseAddr,
					   unsigned int Register)
{
	outb(Register, BaseAddr + INDEXREG);
	return inb(BaseAddr + DATAREG);
}