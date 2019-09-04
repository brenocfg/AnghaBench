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
typedef  int _u32 ;
typedef  int /*<<< orphan*/  _i16 ;

/* Variables and functions */
 int /*<<< orphan*/ * StartResponseLUT ; 

_i16 _sl_GetStartResponseConvert(_u32 Status)
{
    return (_i16)StartResponseLUT[Status & 0x7];
}