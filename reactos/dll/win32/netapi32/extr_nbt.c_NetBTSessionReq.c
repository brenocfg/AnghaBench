#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int len; char* buf; } ;
typedef  TYPE_1__ WSABUF ;
typedef  scalar_t__ UCHAR ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int MAX_DOMAIN_NAME_LEN ; 
 int /*<<< orphan*/  NBR_ADDWORD (scalar_t__*,unsigned int) ; 
 scalar_t__ NBSS_ACK ; 
#define  NBSS_ERR_INSUFFICIENT_RESOURCES 128 
 int NBSS_HDRSIZE ; 
 scalar_t__ NBSS_NACK ; 
 scalar_t__ NBSS_REQ ; 
 scalar_t__ NBSS_RETARGET ; 
 scalar_t__ NRC_GOODRET ; 
 scalar_t__ NRC_NOCALL ; 
 scalar_t__ NRC_REMTFUL ; 
 scalar_t__ NRC_SABORT ; 
 scalar_t__ NRC_SYSTEM ; 
 scalar_t__ NetBTNameEncode (scalar_t__ const*,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int WSARecv (int /*<<< orphan*/ ,TYPE_1__*,int,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WSASend (int /*<<< orphan*/ ,TYPE_1__*,int,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UCHAR NetBTSessionReq(SOCKET fd, const UCHAR *calledName,
 const UCHAR *callingName)
{
    UCHAR buffer[NBSS_HDRSIZE + MAX_DOMAIN_NAME_LEN * 2], ret;
    int r;
    unsigned int len = 0;
    DWORD bytesSent, bytesReceived, recvFlags = 0;
    WSABUF wsaBuf;

    buffer[0] = NBSS_REQ;
    buffer[1] = 0;

    len += NetBTNameEncode(calledName, &buffer[NBSS_HDRSIZE]);
    len += NetBTNameEncode(callingName, &buffer[NBSS_HDRSIZE + len]);

    NBR_ADDWORD(&buffer[2], len);

    wsaBuf.len = len + NBSS_HDRSIZE;
    wsaBuf.buf = (char*)buffer;

    r = WSASend(fd, &wsaBuf, 1, &bytesSent, 0, NULL, NULL);
    if(r < 0 || bytesSent < len + NBSS_HDRSIZE)
    {
        ERR("send failed\n");
        return NRC_SABORT;
    }

    /* I've already set the recv timeout on this socket (if it supports it), so
     * just block.  Hopefully we'll always receive the session acknowledgement
     * within one timeout.
     */
    wsaBuf.len = NBSS_HDRSIZE + 1;
    r = WSARecv(fd, &wsaBuf, 1, &bytesReceived, &recvFlags, NULL, NULL);
    if (r < 0 || bytesReceived < NBSS_HDRSIZE)
        ret = NRC_SABORT;
    else if (buffer[0] == NBSS_NACK)
    {
        if (r == NBSS_HDRSIZE + 1)
        {
            switch (buffer[NBSS_HDRSIZE])
            {
                case NBSS_ERR_INSUFFICIENT_RESOURCES:
                    ret = NRC_REMTFUL;
                    break;
                default:
                    ret = NRC_NOCALL;
            }
        }
        else
            ret = NRC_NOCALL;
    }
    else if (buffer[0] == NBSS_RETARGET)
    {
        FIXME("Got a session retarget, can't deal\n");
        ret = NRC_NOCALL;
    }
    else if (buffer[0] == NBSS_ACK)
        ret = NRC_GOODRET;
    else
        ret = NRC_SYSTEM;

    TRACE("returning 0x%02x\n", ret);
    return ret;
}