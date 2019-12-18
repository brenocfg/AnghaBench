#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lsapi_packet_header {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_5__ {int m_fd; int m_reqState; struct lsapi_packet_header* m_respPktHeader; } ;
typedef  TYPE_1__ LSAPI_Request ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_FinalizeRespHeaders_r (TYPE_1__*) ; 
 int /*<<< orphan*/  LSAPI_Flush_r (TYPE_1__*) ; 
 scalar_t__ LSAPI_PACKET_HEADER_LEN ; 
 int /*<<< orphan*/  LSAPI_RESP_STREAM ; 
 int LSAPI_ST_RESP_BODY ; 
 int LSAPI_ST_RESP_HEADER ; 
 int gsendfile (int,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lsapi_buildPacketHeader (struct lsapi_packet_header*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ write (int,char const*,scalar_t__) ; 

ssize_t LSAPI_sendfile_r( LSAPI_Request * pReq, int fdIn, off_t* off, size_t size )
{
    struct lsapi_packet_header * pHeader = pReq->m_respPktHeader;
    if ( !pReq || (pReq->m_fd == -1) || fdIn == -1 )
        return -1;
    if ( pReq->m_reqState & LSAPI_ST_RESP_HEADER )
    {
        LSAPI_FinalizeRespHeaders_r( pReq );
    }
    pReq->m_reqState |= LSAPI_ST_RESP_BODY;

    LSAPI_Flush_r(pReq);

    lsapi_buildPacketHeader( pHeader, LSAPI_RESP_STREAM,
                            size + LSAPI_PACKET_HEADER_LEN );


    if (write(pReq->m_fd,  (const char *) pHeader, LSAPI_PACKET_HEADER_LEN ) != LSAPI_PACKET_HEADER_LEN)
        return -1;

    return gsendfile( pReq->m_fd, fdIn, off, size );
}