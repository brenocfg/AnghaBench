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
typedef  char WCHAR ;
typedef  char INT ;

/* Variables and functions */

__attribute__((used)) static INT char_to_int(WCHAR c)
{
    if('0' <= c && c <= '9')
        return c - '0';
    if('a' <= c && c <= 'z')
        return c - 'a' + 10;
    if('A' <= c && c <= 'Z')
        return c - 'A' + 10;
    return 100;
}