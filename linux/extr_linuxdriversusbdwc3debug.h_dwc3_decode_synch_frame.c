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
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static inline void dwc3_decode_synch_frame(__u16 i, __u16 l, char *str)
{
	sprintf(str, "Synch Frame(Endpoint = %d, Length = %d)", i, l);
}