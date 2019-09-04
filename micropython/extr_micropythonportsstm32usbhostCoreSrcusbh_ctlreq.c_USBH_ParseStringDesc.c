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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DESC_TYPE_STRING ; 

__attribute__((used)) static void USBH_ParseStringDesc (uint8_t* psrc, 
                                  uint8_t* pdest, 
                                  uint16_t length)
{
  uint16_t strlength;
  uint16_t idx;
  
  /* The UNICODE string descriptor is not NULL-terminated. The string length is
  computed by substracting two from the value of the first byte of the descriptor.
  */
  
  /* Check which is lower size, the Size of string or the length of bytes read 
  from the device */
  
  if ( psrc[1] == USB_DESC_TYPE_STRING)
  { /* Make sure the Descriptor is String Type */
    
    /* psrc[0] contains Size of Descriptor, subtract 2 to get the length of string */      
    strlength = ( ( (psrc[0]-2) <= length) ? (psrc[0]-2) :length); 
    psrc += 2; /* Adjust the offset ignoring the String Len and Descriptor type */
    
    for (idx = 0; idx < strlength; idx+=2 )
    {/* Copy Only the string and ignore the UNICODE ID, hence add the src */
      *pdest =  psrc[idx];
      pdest++;
    }  
    *pdest = 0; /* mark end of string */  
  }
}