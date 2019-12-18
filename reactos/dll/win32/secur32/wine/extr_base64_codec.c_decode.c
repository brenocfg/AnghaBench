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
typedef  char BYTE ;

/* Variables and functions */

__attribute__((used)) static inline BYTE decode(char c)
{
    if( c >= 'A' && c <= 'Z')
        return c - 'A';
    if( c >= 'a' && c <= 'z')
        return c - 'a' + 26;
    if( c >= '0' && c <= '9')
        return c - '0' + 52;
    if( c == '+')
        return 62;
    if( c == '/')
        return 63;
    else
        return 64;
}