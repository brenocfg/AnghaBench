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
typedef  unsigned int _u16 ;
typedef  int _i16 ;

/* Variables and functions */
 unsigned int SL_SOCKET_PAYLOAD_BASE ; 
 int const SL_SOCKET_PAYLOAD_TYPE_MASK ; 
 unsigned int* _SlPayloadByProtocolLUT ; 

_u16 _sl_TruncatePayloadByProtocol(const _i16 sd, const _u16 length)
{
   unsigned int maxLength;


   maxLength = SL_SOCKET_PAYLOAD_BASE + _SlPayloadByProtocolLUT[((sd & SL_SOCKET_PAYLOAD_TYPE_MASK) >> 4)];



   if( length > maxLength )
   {
      return maxLength;
   }
   else
   {
      return length;
   }
}