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
struct client_arg {int writable; int /*<<< orphan*/  client_fd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EBADF ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOTSOCK ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 scalar_t__ errno ; 
 scalar_t__ send (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int ipc_write_str(struct client_arg *client, const char *buf)
{
    size_t count = strlen(buf);
    while (count > 0) {
        ssize_t rc = send(client->client_fd, buf, count, MSG_NOSIGNAL);
        if (rc <= 0) {
            if (rc == 0)
                return -1;

            if (errno == EBADF || errno == ENOTSOCK) {
                client->writable = false;
                return 0;
            }

            if (errno == EINTR || errno == EAGAIN)
                continue;

            return rc;
        }

        count -= rc;
        buf   += rc;
    }

    return 0;
}