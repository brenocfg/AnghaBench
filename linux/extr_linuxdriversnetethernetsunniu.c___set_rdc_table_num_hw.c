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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int HOST_INFO_MACRDCTBLN ; 
 int HOST_INFO_MPR ; 
 int nr64_mac (unsigned long) ; 
 int /*<<< orphan*/  nw64_mac (unsigned long,int) ; 

__attribute__((used)) static void __set_rdc_table_num_hw(struct niu *np, unsigned long reg,
				   int num, int mac_pref)
{
	u64 val = nr64_mac(reg);
	val &= ~(HOST_INFO_MACRDCTBLN | HOST_INFO_MPR);
	val |= num;
	if (mac_pref)
		val |= HOST_INFO_MPR;
	nw64_mac(reg, val);
}