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
struct timeval {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct Output {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int parse_state_machine (struct Output*,unsigned char*,size_t) ; 
 size_t recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 

__attribute__((used)) static int
clean_response_queue(struct Output *out, SOCKET fd)
{
    fd_set readfds;
    struct timeval tv = {0,0};
    int x;
    int nfds;
    unsigned char buf[1024];
    size_t bytes_read;

    FD_ZERO(&readfds);
#ifdef _MSC_VER
#pragma warning(disable:4127)
#endif
    FD_SET(fd, &readfds);
    nfds = (int)fd;

    x = select(nfds, &readfds, 0, 0, &tv);
    if (x == 0)
        return 1;
    if (x < 0) {
        LOG(0, "redis:select() failed\n");
        exit(1);
    }
    if (x != 1) {
        LOG(0, "redis:select() failed\n");
        exit(1);
    }

    /*
     * Data exists, so parse it
     */
    bytes_read = recv(fd, (char*)buf, sizeof(buf), 0);
    if (bytes_read == 0) {
        LOG(0, "redis:recv() failed\n");
        exit(1);
    }

    return parse_state_machine(out, buf, bytes_read);
}