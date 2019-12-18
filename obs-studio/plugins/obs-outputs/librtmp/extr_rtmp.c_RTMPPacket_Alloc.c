#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {char* m_body; scalar_t__ m_nBytesRead; } ;
typedef  TYPE_1__ RTMPPacket ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ RTMP_MAX_HEADER_SIZE ; 
 scalar_t__ SIZE_MAX ; 
 int TRUE ; 
 char* calloc (int,scalar_t__) ; 

int
RTMPPacket_Alloc(RTMPPacket *p, uint32_t nSize)
{
    char *ptr;
#if ARCH_BITS == 32
    if (nSize > SIZE_MAX - RTMP_MAX_HEADER_SIZE)
        return FALSE;
#endif

    ptr = calloc(1, nSize + RTMP_MAX_HEADER_SIZE);
    if (!ptr)
        return FALSE;
    p->m_body = ptr + RTMP_MAX_HEADER_SIZE;
    p->m_nBytesRead = 0;
    return TRUE;
}