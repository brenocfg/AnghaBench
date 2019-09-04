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
typedef  int /*<<< orphan*/  u32 ;
struct isp116x {int dummy; } ;

/* Variables and functions */
 unsigned int ISP116x_WRITE_OFFSET ; 
 int /*<<< orphan*/  isp116x_write_addr (struct isp116x*,unsigned int) ; 
 int /*<<< orphan*/  isp116x_write_data32 (struct isp116x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp116x_write_reg32(struct isp116x *isp116x, unsigned reg,
				unsigned val)
{
	isp116x_write_addr(isp116x, reg | ISP116x_WRITE_OFFSET);
	isp116x_write_data32(isp116x, (u32) val);
}