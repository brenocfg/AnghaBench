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
typedef  int /*<<< orphan*/  u16 ;
struct isp116x {int /*<<< orphan*/  data_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp116x_delay (struct isp116x*,int) ; 

__attribute__((used)) static inline u16 isp116x_raw_read_data16(struct isp116x *isp116x)
{
	u16 val;

	val = __raw_readw(isp116x->data_reg);
	isp116x_delay(isp116x, 150);
	return val;
}