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
typedef  char u8 ;

/* Variables and functions */

__attribute__((used)) static u8 key_char2num(u8 ch)
{
    if((ch>='0')&&(ch<='9'))
        return ch - '0';
    else if ((ch>='a')&&(ch<='f'))
        return ch - 'a' + 10;
    else if ((ch>='A')&&(ch<='F'))
        return ch - 'A' + 10;
    else
	 return 0xff;
}