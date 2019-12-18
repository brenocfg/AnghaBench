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
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  nodelay ;
typedef  int /*<<< orphan*/  achPeer ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int lsapi_accept( int fdListen )
{
    int         fd;
    int         nodelay = 1;
    socklen_t   len;
    char        achPeer[128];

    len = sizeof( achPeer );
    fd = accept( fdListen, (struct sockaddr *)&achPeer, &len );
    if ( fd != -1 )
    {
        if (((struct sockaddr *)&achPeer)->sa_family == AF_INET )
        {
            setsockopt( fd, IPPROTO_TCP, TCP_NODELAY,
                    (char *)&nodelay, sizeof(nodelay));
        }

        //OPTIMIZATION
        //if ( s_accept_notify )
        //    notify_req_received( fd );
    }
    return fd;

}