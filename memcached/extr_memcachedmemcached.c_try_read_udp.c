#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  enum try_read_result { ____Placeholder_try_read_result } try_read_result ;
struct TYPE_8__ {int request_addr_size; unsigned char request_id; int rbytes; scalar_t__ rbuf; scalar_t__ rcurr; TYPE_2__* thread; int /*<<< orphan*/  request_addr; int /*<<< orphan*/  rsize; int /*<<< orphan*/  sfd; } ;
typedef  TYPE_3__ conn ;
struct TYPE_6__ {int bytes_read; int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int READ_DATA_RECEIVED ; 
 int READ_NO_DATA_RECEIVED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  out_string (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int recvfrom (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

__attribute__((used)) static enum try_read_result try_read_udp(conn *c) {
    int res;

    assert(c != NULL);

    c->request_addr_size = sizeof(c->request_addr);
    res = recvfrom(c->sfd, c->rbuf, c->rsize,
                   0, (struct sockaddr *)&c->request_addr,
                   &c->request_addr_size);
    if (res > 8) {
        unsigned char *buf = (unsigned char *)c->rbuf;
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.bytes_read += res;
        pthread_mutex_unlock(&c->thread->stats.mutex);

        /* Beginning of UDP packet is the request ID; save it. */
        c->request_id = buf[0] * 256 + buf[1];

        /* If this is a multi-packet request, drop it. */
        if (buf[4] != 0 || buf[5] != 1) {
            out_string(c, "SERVER_ERROR multi-packet request not supported");
            return READ_NO_DATA_RECEIVED;
        }

        /* Don't care about any of the rest of the header. */
        res -= 8;
        memmove(c->rbuf, c->rbuf + 8, res);

        c->rbytes = res;
        c->rcurr = c->rbuf;
        return READ_DATA_RECEIVED;
    }
    return READ_NO_DATA_RECEIVED;
}