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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int FALSE ; 

bfd_boolean
aarch64_sve_dupm_mov_immediate_p (uint64_t uvalue, int esize)
{
  int64_t svalue = uvalue;
  uint64_t upper = (uint64_t) -1 << (esize * 4) << (esize * 4);

  if ((uvalue & ~upper) != uvalue && (uvalue | upper) != uvalue)
    return FALSE;
  if (esize <= 4 || (uint32_t) uvalue == (uint32_t) (uvalue >> 32))
    {
      svalue = (int32_t) uvalue;
      if (esize <= 2 || (uint16_t) uvalue == (uint16_t) (uvalue >> 16))
	{
	  svalue = (int16_t) uvalue;
	  if (esize == 1 || (uint8_t) uvalue == (uint8_t) (uvalue >> 8))
	    return FALSE;
	}
    }
  if ((svalue & 0xff) == 0)
    svalue /= 256;
  return svalue < -128 || svalue >= 128;
}