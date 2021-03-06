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
typedef  enum GA_REG { ____Placeholder_GA_REG } GA_REG ;

/* Variables and functions */
 int /*<<< orphan*/  ODIE_ADDR_IO (unsigned int) ; 
 int /*<<< orphan*/  ODIE_DATA_IO (unsigned int) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sscape_write_unsafe(unsigned io_base, enum GA_REG reg,
				       unsigned char val)
{
	outb(reg, ODIE_ADDR_IO(io_base));
	outb(val, ODIE_DATA_IO(io_base));
}