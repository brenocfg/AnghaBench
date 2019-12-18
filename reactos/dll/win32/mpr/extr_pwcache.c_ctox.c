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
typedef  char CHAR ;

/* Variables and functions */

__attribute__((used)) static inline signed char ctox( CHAR x )
{
    if( ( x >= '0' ) && ( x <= '9' ) )
        return x - '0';
    if( ( x >= 'A' ) && ( x <= 'F' ) )
        return x - 'A' + 10;
    if( ( x >= 'a' ) && ( x <= 'a' ) )
        return x - 'a' + 10;
    return -1;
}