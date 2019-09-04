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
typedef  scalar_t__ u32 ;
struct iss_device {scalar_t__* regs; } ;
typedef  enum iss_mem_resources { ____Placeholder_iss_mem_resources } iss_mem_resources ;

/* Variables and functions */
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline
void iss_reg_write(struct iss_device *iss, enum iss_mem_resources res,
		   u32 offset, u32 value)
{
	writel(value, iss->regs[res] + offset);
}