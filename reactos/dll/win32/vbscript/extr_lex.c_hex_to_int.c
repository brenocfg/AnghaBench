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

/* Variables and functions */

__attribute__((used)) static int hex_to_int(WCHAR c)
{
    if('0' <= c && c <= '9')
        return c-'0';
    if('a' <= c && c <= 'f')
        return c+10-'a';
    if('A' <= c && c <= 'F')
        return c+10-'A';
    return -1;
}