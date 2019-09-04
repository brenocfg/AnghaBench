#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* m_bytes; int m_iLen; } ;
struct lsapi_packet_header {scalar_t__ m_versionB0; scalar_t__ m_versionB1; char m_type; int m_flag; TYPE_1__ m_packetLen; } ;

/* Variables and functions */
 int LSAPI_ENDIAN ; 
 int LSAPI_ENDIAN_BIT ; 
 scalar_t__ LSAPI_VERSION_B0 ; 
 scalar_t__ LSAPI_VERSION_B1 ; 

__attribute__((used)) static inline int verifyHeader( struct lsapi_packet_header * pHeader, char pktType )
{
    if (( LSAPI_VERSION_B0 != pHeader->m_versionB0 )||
        ( LSAPI_VERSION_B1 != pHeader->m_versionB1 )||
        ( pktType != pHeader->m_type ))
        return -1;
    if ( LSAPI_ENDIAN != (pHeader->m_flag & LSAPI_ENDIAN_BIT ))
    {
        register char b;
        b = pHeader->m_packetLen.m_bytes[0];
        pHeader->m_packetLen.m_bytes[0] = pHeader->m_packetLen.m_bytes[3];
        pHeader->m_packetLen.m_bytes[3] = b;
        b = pHeader->m_packetLen.m_bytes[1];
        pHeader->m_packetLen.m_bytes[1] = pHeader->m_packetLen.m_bytes[2];
        pHeader->m_packetLen.m_bytes[2] = b;
    }
    return pHeader->m_packetLen.m_iLen;
}