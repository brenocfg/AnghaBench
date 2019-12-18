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
struct Output {int dummy; } ;
typedef  scalar_t__ ptrdiff_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  UNUSEDPARM (struct Output*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ memcmp (unsigned char*,char*,int) ; 
 size_t recv_line (int /*<<< orphan*/ ,unsigned char*,int) ; 
 size_t send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
redis_out_close(struct Output *out, FILE *fp)
{
    ptrdiff_t fd = (ptrdiff_t)fp;
    size_t count;
    unsigned char line[1024];

    UNUSEDPARM(out);

    count = send((SOCKET)fd, "PING\r\n", 6, 0);
    if (count != 6) {
        LOG(0, "redis: send(ping) failed\n");
        exit(1);
    }

    count = recv_line((SOCKET)fd, line, sizeof(line));
    if (count != 7 && memcmp(line, "+PONG\r\n", 7) != 0) {
        LOG(0, "redis: unexpected response from redis server: %s\n", line);
        exit(1);
    }
}