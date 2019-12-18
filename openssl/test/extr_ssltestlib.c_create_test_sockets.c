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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  inet_addr (char const*) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int set_nb (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int create_test_sockets(int *cfd, int *sfd)
{
    struct sockaddr_in sin;
    const char *host = "127.0.0.1";
    int cfd_connected = 0, ret = 0;
    socklen_t slen = sizeof(sin);
    int afd = -1;

    *cfd = -1;
    *sfd = -1;

    memset ((char *) &sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(host);

    afd = socket(AF_INET, SOCK_STREAM, 0);
    if (afd < 0)
        return 0;

    if (bind(afd, (struct sockaddr*)&sin, sizeof(sin)) < 0)
        goto out;

    if (getsockname(afd, (struct sockaddr*)&sin, &slen) < 0)
        goto out;

    if (listen(afd, 1) < 0)
        goto out;

    *cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*cfd < 0)
        goto out;

    if (set_nb(afd) == -1)
        goto out;

    while (*sfd == -1 || !cfd_connected ) {
        *sfd = accept(afd, NULL, 0);
        if (*sfd == -1 && errno != EAGAIN)
            goto out;

        if (!cfd_connected && connect(*cfd, (struct sockaddr*)&sin, sizeof(sin)) < 0)
            goto out;
        else
            cfd_connected = 1;
    }

    if (set_nb(*cfd) == -1 || set_nb(*sfd) == -1)
        goto out;
    ret = 1;
    goto success;

out:
        if (*cfd != -1)
            close(*cfd);
        if (*sfd != -1)
            close(*sfd);
success:
        if (afd != -1)
            close(afd);
    return ret;
}