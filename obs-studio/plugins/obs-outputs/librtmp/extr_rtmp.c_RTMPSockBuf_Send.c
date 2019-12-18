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
struct TYPE_3__ {int /*<<< orphan*/  sb_socket; scalar_t__ sb_ssl; } ;
typedef  TYPE_1__ RTMPSockBuf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int TLS_write (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netstackdump ; 
 int send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

int
RTMPSockBuf_Send(RTMPSockBuf *sb, const char *buf, int len)
{
    int rc;

#if defined(RTMP_NETSTACK_DUMP)
    fwrite(buf, 1, len, netstackdump);
#endif

#if defined(CRYPTO) && !defined(NO_SSL)
    if (sb->sb_ssl)
    {
        rc = TLS_write(sb->sb_ssl, buf, len);
    }
    else
#endif
    {
        rc = send(sb->sb_socket, buf, len, MSG_NOSIGNAL);
    }
    return rc;
}