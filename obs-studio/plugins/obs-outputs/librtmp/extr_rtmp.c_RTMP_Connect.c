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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  service ;
struct TYPE_11__ {int /*<<< orphan*/  av_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  port; TYPE_4__ hostname; int /*<<< orphan*/  socksport; TYPE_4__ sockshost; } ;
struct TYPE_8__ {scalar_t__ addrLen; } ;
struct TYPE_10__ {int last_error_code; int /*<<< orphan*/  m_bSendCounter; TYPE_2__ Link; TYPE_1__ m_bindIP; } ;
typedef  int /*<<< orphan*/  RTMPPacket ;
typedef  TYPE_3__ RTMP ;
typedef  int /*<<< orphan*/  HOSTENT ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  RTMP_Connect0 (TYPE_3__*,struct sockaddr*,scalar_t__) ; 
 int RTMP_Connect1 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTMP_LOGERROR ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSAHOST_NOT_FOUND ; 
 int /*<<< orphan*/  add_addr_info (struct sockaddr_storage*,scalar_t__*,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/ * gethostbyname (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 

int
RTMP_Connect(RTMP *r, RTMPPacket *cp)
{
#ifdef _WIN32
    HOSTENT *h;
#endif
    struct sockaddr_storage service;
    socklen_t addrlen = 0;
    socklen_t addrlen_hint = 0;
    int socket_error = 0;

    if (!r->Link.hostname.av_len)
        return FALSE;

#ifdef _WIN32
    //COMODO security software sandbox blocks all DNS by returning "host not found"
    h = gethostbyname("localhost");
    if (!h && GetLastError() == WSAHOST_NOT_FOUND)
    {
        r->last_error_code = WSAHOST_NOT_FOUND;
        RTMP_Log(RTMP_LOGERROR, "RTMP_Connect: Connection test failed. This error is likely caused by Comodo Internet Security running OBS in sandbox mode. Please add OBS to the Comodo automatic sandbox exclusion list, restart OBS and try again (11001).");
        return FALSE;
    }
#endif

    memset(&service, 0, sizeof(service));

    if (r->m_bindIP.addrLen)
        addrlen_hint = r->m_bindIP.addrLen;

    if (r->Link.socksport)
    {
        /* Connect via SOCKS */
        if (!add_addr_info(&service, &addrlen, &r->Link.sockshost, r->Link.socksport, addrlen_hint, &socket_error))
        {
            r->last_error_code = socket_error;
            return FALSE;
        }
    }
    else
    {
        /* Connect directly */
        if (!add_addr_info(&service, &addrlen, &r->Link.hostname, r->Link.port, addrlen_hint, &socket_error))
        {
            r->last_error_code = socket_error;
            return FALSE;
        }
    }

    if (!RTMP_Connect0(r, (struct sockaddr *)&service, addrlen))
        return FALSE;

    r->m_bSendCounter = TRUE;

    return RTMP_Connect1(r, cp);
}