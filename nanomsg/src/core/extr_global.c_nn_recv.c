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
struct nn_msghdr {int msg_iovlen; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct nn_iovec* msg_iov; } ;
struct nn_iovec {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int nn_recvmsg (int,struct nn_msghdr*,int) ; 

int nn_recv (int s, void *buf, size_t len, int flags)
{
    struct nn_iovec iov;
    struct nn_msghdr hdr;

    iov.iov_base = buf;
    iov.iov_len = len;

    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = NULL;
    hdr.msg_controllen = 0;

    return nn_recvmsg (s, &hdr, flags);
}