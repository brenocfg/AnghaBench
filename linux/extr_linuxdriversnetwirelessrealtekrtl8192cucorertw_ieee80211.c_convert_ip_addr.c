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
typedef  int u8 ;

/* Variables and functions */
 int key_char2num (int) ; 

u8 convert_ip_addr(u8 hch, u8 mch, u8 lch)
{
    return ((key_char2num(hch) * 100) + (key_char2num(mch) * 10 ) + key_char2num(lch));
}