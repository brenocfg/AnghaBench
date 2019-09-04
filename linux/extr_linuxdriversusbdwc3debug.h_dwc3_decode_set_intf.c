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
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static inline void dwc3_decode_set_intf(__u8 v, __u16 i, char *str)
{
	sprintf(str, "Set Interface(Intf = %d, Alt.Setting = %d)", i, v);
}