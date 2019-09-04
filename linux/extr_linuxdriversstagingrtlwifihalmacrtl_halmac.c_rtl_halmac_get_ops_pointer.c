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
struct rtl_halmac_ops {int dummy; } ;

/* Variables and functions */
 struct rtl_halmac_ops rtl_halmac_operation ; 

struct rtl_halmac_ops *rtl_halmac_get_ops_pointer(void)
{
	return &rtl_halmac_operation;
}