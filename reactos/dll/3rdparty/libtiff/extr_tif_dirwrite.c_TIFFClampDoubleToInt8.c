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
typedef  int int8 ;

/* Variables and functions */

__attribute__((used)) static int8 TIFFClampDoubleToInt8( double val )
{
    if( val > 127 )
        return 127;
    if( val < -128 || val != val )
        return -128;
    return (int8)val;
}