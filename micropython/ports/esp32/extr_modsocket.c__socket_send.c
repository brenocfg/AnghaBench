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
struct TYPE_3__ {int retries; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ socket_obj_t ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  MP_ETIMEDOUT ; 
 int /*<<< orphan*/  MP_THREAD_GIL_ENTER () ; 
 int /*<<< orphan*/  MP_THREAD_GIL_EXIT () ; 
 int /*<<< orphan*/  check_for_exceptions () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exception_from_errno (scalar_t__) ; 
 int lwip_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  mp_raise_OSError (int /*<<< orphan*/ ) ; 

int _socket_send(socket_obj_t *sock, const char *data, size_t datalen) {
    int sentlen = 0;
    for (int i=0; i<=sock->retries && sentlen < datalen; i++) {
        MP_THREAD_GIL_EXIT();
        int r = lwip_write(sock->fd, data+sentlen, datalen-sentlen);
        MP_THREAD_GIL_ENTER();
        if (r < 0 && errno != EWOULDBLOCK) exception_from_errno(errno);
        if (r > 0) sentlen += r;
        check_for_exceptions();
    }
    if (sentlen == 0) mp_raise_OSError(MP_ETIMEDOUT);
    return sentlen;
}