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

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static inline void dwc3_decode_set_isoch_delay(__u8 v, char *str)
{
	sprintf(str, "Set Isochronous Delay(Delay = %d ns)", v);
}