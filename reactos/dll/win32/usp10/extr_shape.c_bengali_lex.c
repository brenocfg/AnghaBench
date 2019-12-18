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
typedef  int WCHAR ;

/* Variables and functions */
 int lex_Ra ; 
 int unicode_lex (int) ; 

__attribute__((used)) static int bengali_lex(WCHAR c)
{
    switch (c)
    {
        case 0x09B0: return lex_Ra;
        default:
            return unicode_lex(c);
    }
}