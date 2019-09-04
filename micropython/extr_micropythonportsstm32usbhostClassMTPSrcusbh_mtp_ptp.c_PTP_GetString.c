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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void PTP_GetString (uint8_t *str, uint8_t* data, uint16_t *len)
{
  uint16_t strlength;
  uint16_t idx;
  
  *len = data[0];
  strlength = 2 * data[0]; 
  data ++; /* Adjust the offset ignoring the String Len */
  
  for (idx = 0; idx < strlength; idx+=2 )
  {
    /* Copy Only the string and ignore the UNICODE ID, hence add the src */
    *str =  data[idx];
    str++;
  }  
  *str = 0; /* mark end of string */  
}