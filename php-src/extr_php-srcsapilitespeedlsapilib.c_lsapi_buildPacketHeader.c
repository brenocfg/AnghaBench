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
struct TYPE_2__ {int m_iLen; } ;
struct lsapi_packet_header {char m_type; TYPE_1__ m_packetLen; int /*<<< orphan*/  m_flag; int /*<<< orphan*/  m_versionB1; int /*<<< orphan*/  m_versionB0; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_ENDIAN ; 
 int /*<<< orphan*/  LSAPI_VERSION_B0 ; 
 int /*<<< orphan*/  LSAPI_VERSION_B1 ; 

__attribute__((used)) static inline void lsapi_buildPacketHeader( struct lsapi_packet_header * pHeader,
                                char type, int len )
{
    pHeader->m_versionB0 = LSAPI_VERSION_B0;  /* LSAPI protocol version */
    pHeader->m_versionB1 = LSAPI_VERSION_B1;
    pHeader->m_type      = type;
    pHeader->m_flag      = LSAPI_ENDIAN;
    pHeader->m_packetLen.m_iLen = len;
}