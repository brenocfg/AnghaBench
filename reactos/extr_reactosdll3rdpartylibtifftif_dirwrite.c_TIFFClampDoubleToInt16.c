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
typedef  int int16 ;

/* Variables and functions */

__attribute__((used)) static int16 TIFFClampDoubleToInt16( double val )
{
    if( val > 32767 )
        return 32767;
    if( val < -32768 || val != val )
        return -32768;
    return (int16)val;
}