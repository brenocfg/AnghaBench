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
typedef  int _u16 ;
typedef  int _i8 ;
typedef  int _i16 ;

/* Variables and functions */

_u16 sl_Htons( _u16 val )
{
  _i16 i = 1; 
  _i8 *p = (_i8 *)&i;  
  if (p[0] == 1) /* little endian */
  {
    p[0] = ((_i8* )&val)[1];
    p[1] = ((_i8* )&val)[0];
    return i;
  }
  else /* big endian */
  {
    return val; 
  }
}