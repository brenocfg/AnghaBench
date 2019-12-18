#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct msghdr {int msg_controllen; int /*<<< orphan*/  ipi6_addr; int /*<<< orphan*/ ** msg_control; struct in_addr ipi_spec_dst; int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct in_pktinfo {int msg_controllen; int /*<<< orphan*/  ipi6_addr; int /*<<< orphan*/ ** msg_control; struct in_addr ipi_spec_dst; int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct in6_pktinfo {int msg_controllen; int /*<<< orphan*/  ipi6_addr; int /*<<< orphan*/ ** msg_control; struct in_addr ipi_spec_dst; int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct cmsghdr {void* cmsg_len; int /*<<< orphan*/  cmsg_type; void* cmsg_level; } ;
typedef  int ssize_t ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  count; int /*<<< orphan*/  iovs; } ;
typedef  TYPE_4__ ngx_iovec_t ;
typedef  int ngx_err_t ;
struct TYPE_13__ {TYPE_3__* write; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; TYPE_2__* local_sockaddr; TYPE_1__* listening; scalar_t__ socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_5__ ngx_connection_t ;
typedef  int /*<<< orphan*/  msg_control6 ;
typedef  int /*<<< orphan*/  msg_control ;
struct TYPE_11__ {int error; } ;
struct TYPE_10__ {scalar_t__ sa_family; } ;
struct TYPE_9__ {scalar_t__ wildcard; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 void* CMSG_LEN (int) ; 
 int CMSG_SPACE (int) ; 
 void* IPPROTO_IP ; 
 void* IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 int /*<<< orphan*/  IP_PKTINFO ; 
 int /*<<< orphan*/  IP_SENDSRCADDR ; 
 int NGX_AGAIN ; 
#define  NGX_EAGAIN 129 
#define  NGX_EINTR 128 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_5__*,int,char*) ; 
 int ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (struct msghdr*,int) ; 
 int sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ngx_sendmsg(ngx_connection_t *c, ngx_iovec_t *vec)
{
    ssize_t        n;
    ngx_err_t      err;
    struct msghdr  msg;

#if (NGX_HAVE_MSGHDR_MSG_CONTROL)

#if (NGX_HAVE_IP_SENDSRCADDR)
    u_char         msg_control[CMSG_SPACE(sizeof(struct in_addr))];
#elif (NGX_HAVE_IP_PKTINFO)
    u_char         msg_control[CMSG_SPACE(sizeof(struct in_pktinfo))];
#endif

#if (NGX_HAVE_INET6 && NGX_HAVE_IPV6_RECVPKTINFO)
    u_char         msg_control6[CMSG_SPACE(sizeof(struct in6_pktinfo))];
#endif

#endif

    ngx_memzero(&msg, sizeof(struct msghdr));

    if (c->socklen) {
        msg.msg_name = c->sockaddr;
        msg.msg_namelen = c->socklen;
    }

    msg.msg_iov = vec->iovs;
    msg.msg_iovlen = vec->count;

#if (NGX_HAVE_MSGHDR_MSG_CONTROL)

    if (c->listening && c->listening->wildcard && c->local_sockaddr) {

#if (NGX_HAVE_IP_SENDSRCADDR)

        if (c->local_sockaddr->sa_family == AF_INET) {
            struct cmsghdr      *cmsg;
            struct in_addr      *addr;
            struct sockaddr_in  *sin;

            msg.msg_control = &msg_control;
            msg.msg_controllen = sizeof(msg_control);

            cmsg = CMSG_FIRSTHDR(&msg);
            cmsg->cmsg_level = IPPROTO_IP;
            cmsg->cmsg_type = IP_SENDSRCADDR;
            cmsg->cmsg_len = CMSG_LEN(sizeof(struct in_addr));

            sin = (struct sockaddr_in *) c->local_sockaddr;

            addr = (struct in_addr *) CMSG_DATA(cmsg);
            *addr = sin->sin_addr;
        }

#elif (NGX_HAVE_IP_PKTINFO)

        if (c->local_sockaddr->sa_family == AF_INET) {
            struct cmsghdr      *cmsg;
            struct in_pktinfo   *pkt;
            struct sockaddr_in  *sin;

            msg.msg_control = &msg_control;
            msg.msg_controllen = sizeof(msg_control);

            cmsg = CMSG_FIRSTHDR(&msg);
            cmsg->cmsg_level = IPPROTO_IP;
            cmsg->cmsg_type = IP_PKTINFO;
            cmsg->cmsg_len = CMSG_LEN(sizeof(struct in_pktinfo));

            sin = (struct sockaddr_in *) c->local_sockaddr;

            pkt = (struct in_pktinfo *) CMSG_DATA(cmsg);
            ngx_memzero(pkt, sizeof(struct in_pktinfo));
            pkt->ipi_spec_dst = sin->sin_addr;
        }

#endif

#if (NGX_HAVE_INET6 && NGX_HAVE_IPV6_RECVPKTINFO)

        if (c->local_sockaddr->sa_family == AF_INET6) {
            struct cmsghdr       *cmsg;
            struct in6_pktinfo   *pkt6;
            struct sockaddr_in6  *sin6;

            msg.msg_control = &msg_control6;
            msg.msg_controllen = sizeof(msg_control6);

            cmsg = CMSG_FIRSTHDR(&msg);
            cmsg->cmsg_level = IPPROTO_IPV6;
            cmsg->cmsg_type = IPV6_PKTINFO;
            cmsg->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));

            sin6 = (struct sockaddr_in6 *) c->local_sockaddr;

            pkt6 = (struct in6_pktinfo *) CMSG_DATA(cmsg);
            ngx_memzero(pkt6, sizeof(struct in6_pktinfo));
            pkt6->ipi6_addr = sin6->sin6_addr;
        }

#endif
    }

#endif

eintr:

    n = sendmsg(c->fd, &msg, 0);

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "sendmsg: %z of %uz", n, vec->size);

    if (n == -1) {
        err = ngx_errno;

        switch (err) {
        case NGX_EAGAIN:
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, err,
                           "sendmsg() not ready");
            return NGX_AGAIN;

        case NGX_EINTR:
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, err,
                           "sendmsg() was interrupted");
            goto eintr;

        default:
            c->write->error = 1;
            ngx_connection_error(c, err, "sendmsg() failed");
            return NGX_ERROR;
        }
    }

    return n;
}