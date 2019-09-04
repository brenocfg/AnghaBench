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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int regstep; scalar_t__ base; } ;
struct c67x00_device {TYPE_1__ hpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_T_CYC_NS ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hpi_write_reg(struct c67x00_device *dev, int reg, u16 value)
{
	ndelay(HPI_T_CYC_NS);
	__raw_writew(value, dev->hpi.base + reg * dev->hpi.regstep);
}