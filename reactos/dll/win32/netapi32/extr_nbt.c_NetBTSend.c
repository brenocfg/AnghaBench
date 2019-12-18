#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wsaBufs ;
struct TYPE_8__ {int len; char* buf; } ;
typedef  TYPE_1__ WSABUF ;
typedef  scalar_t__ UCHAR ;
struct TYPE_11__ {int /*<<< orphan*/  xmit_success; } ;
struct TYPE_10__ {scalar_t__ fd; } ;
struct TYPE_9__ {int ncb_length; scalar_t__ ncb_buffer; } ;
typedef  TYPE_2__* PNCB ;
typedef  TYPE_3__ NetBTSession ;
typedef  TYPE_4__ NetBTAdapter ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int,int) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  NBR_ADDWORD (scalar_t__*,int) ; 
 int NBSS_HDRSIZE ; 
 scalar_t__ NBSS_MSG ; 
 scalar_t__ NRC_BADDR ; 
 scalar_t__ NRC_ENVNOTDEF ; 
 scalar_t__ NRC_GOODRET ; 
 scalar_t__ NRC_INVADDRESS ; 
 scalar_t__ NRC_SABORT ; 
 scalar_t__ NRC_SNUMOUT ; 
 int /*<<< orphan*/  NetBIOSHangupSession (TYPE_2__*) ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int WSASend (scalar_t__,TYPE_1__*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UCHAR NetBTSend(void *adapt, void *sess, PNCB ncb)
{
    NetBTAdapter *adapter = adapt;
    NetBTSession *session = sess;
    UCHAR buffer[NBSS_HDRSIZE], ret;
    int r;
    WSABUF wsaBufs[2];
    DWORD bytesSent;

    TRACE("adapt %p, session %p, NCB %p\n", adapt, session, ncb);

    if (!adapter) return NRC_ENVNOTDEF;
    if (!ncb) return NRC_INVADDRESS;
    if (!ncb->ncb_buffer) return NRC_BADDR;
    if (!session) return NRC_SNUMOUT;
    if (session->fd == INVALID_SOCKET) return NRC_SNUMOUT;

    buffer[0] = NBSS_MSG;
    buffer[1] = 0;
    NBR_ADDWORD(&buffer[2], ncb->ncb_length);

    wsaBufs[0].len = NBSS_HDRSIZE;
    wsaBufs[0].buf = (char*)buffer;
    wsaBufs[1].len = ncb->ncb_length;
    wsaBufs[1].buf = (char*)ncb->ncb_buffer;

    r = WSASend(session->fd, wsaBufs, sizeof(wsaBufs) / sizeof(wsaBufs[0]),
     &bytesSent, 0, NULL, NULL);
    if (r == SOCKET_ERROR)
    {
        NetBIOSHangupSession(ncb);
        ret = NRC_SABORT;
    }
    else if (bytesSent < NBSS_HDRSIZE + ncb->ncb_length)
    {
        FIXME("Only sent %d bytes (of %d), hanging up session\n", bytesSent,
         NBSS_HDRSIZE + ncb->ncb_length);
        NetBIOSHangupSession(ncb);
        ret = NRC_SABORT;
    }
    else
    {
        ret = NRC_GOODRET;
        adapter->xmit_success++;
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}