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
typedef  int /*<<< orphan*/  _u8 ;
typedef  scalar_t__ _u16 ;

/* Variables and functions */

_u16 _sl_Strlen(const _u8 *buffer)
{
    _u16 len = 0;
    if( buffer != NULL )
    {
      while(*buffer++) len++;
    }
    return len;
}