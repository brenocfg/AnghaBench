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
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL word_break_causing(WCHAR chr)
{
    /* we are working within a string of characters already guareented to
       be within one script, Syriac, so we do not worry about any character
       other than the space character outside of that range */
    return (chr == 0 || chr == 0x20 );
}