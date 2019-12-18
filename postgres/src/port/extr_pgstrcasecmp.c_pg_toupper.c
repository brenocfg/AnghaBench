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

/* Variables and functions */
 scalar_t__ IS_HIGHBIT_SET (unsigned char) ; 
 scalar_t__ islower (unsigned char) ; 
 unsigned char toupper (unsigned char) ; 

unsigned char
pg_toupper(unsigned char ch)
{
	if (ch >= 'a' && ch <= 'z')
		ch += 'A' - 'a';
	else if (IS_HIGHBIT_SET(ch) && islower(ch))
		ch = toupper(ch);
	return ch;
}