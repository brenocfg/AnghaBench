#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sn_type; } ;
union sctp_notification {int se_on; int sctp_sender_dry_event; TYPE_1__ sn_header; scalar_t__ se_type; scalar_t__ se_assoc_id; } ;
struct sctp_event_subscribe {int se_on; int sctp_sender_dry_event; TYPE_1__ sn_header; scalar_t__ se_type; scalar_t__ se_assoc_id; } ;
struct sctp_event {int dummy; } ;
struct msghdr {int msg_iovlen; int msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  snp ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_8__ {int /*<<< orphan*/  notification_context; int /*<<< orphan*/  (* handle_notifications ) (TYPE_3__*,int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_2__ bio_dgram_sctp_data ;
struct TYPE_9__ {int /*<<< orphan*/  num; scalar_t__ ptr; } ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int MSG_NOTIFICATION ; 
 int /*<<< orphan*/  MSG_PEEK ; 
 int O_NONBLOCK ; 
 scalar_t__ SCTP_AUTHENTICATION_EVENT ; 
 int /*<<< orphan*/  SCTP_EVENT ; 
 int /*<<< orphan*/  SCTP_EVENTS ; 
 scalar_t__ SCTP_SENDER_DRY_EVENT ; 
 int /*<<< orphan*/  dgram_sctp_handle_auth_free_key_event (TYPE_3__*,union sctp_notification*) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_last_socket_error () ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union sctp_notification*,int*) ; 
 int /*<<< orphan*/  memset (union sctp_notification*,int /*<<< orphan*/ ,int) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union sctp_notification*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int dgram_sctp_wait_for_dry(BIO *b)
{
    int is_dry = 0;
    int sockflags = 0;
    int n, ret;
    union sctp_notification snp;
    struct msghdr msg;
    struct iovec iov;
#  ifdef SCTP_EVENT
    struct sctp_event event;
#  else
    struct sctp_event_subscribe event;
    socklen_t eventsize;
#  endif
    bio_dgram_sctp_data *data = (bio_dgram_sctp_data *) b->ptr;

    /* set sender dry event */
#  ifdef SCTP_EVENT
    memset(&event, 0, sizeof(event));
    event.se_assoc_id = 0;
    event.se_type = SCTP_SENDER_DRY_EVENT;
    event.se_on = 1;
    ret =
        setsockopt(b->num, IPPROTO_SCTP, SCTP_EVENT, &event,
                   sizeof(struct sctp_event));
#  else
    eventsize = sizeof(struct sctp_event_subscribe);
    ret = getsockopt(b->num, IPPROTO_SCTP, SCTP_EVENTS, &event, &eventsize);
    if (ret < 0)
        return -1;

    event.sctp_sender_dry_event = 1;

    ret =
        setsockopt(b->num, IPPROTO_SCTP, SCTP_EVENTS, &event,
                   sizeof(struct sctp_event_subscribe));
#  endif
    if (ret < 0)
        return -1;

    /* peek for notification */
    memset(&snp, 0, sizeof(snp));
    iov.iov_base = (char *)&snp;
    iov.iov_len = sizeof(union sctp_notification);
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_flags = 0;

    n = recvmsg(b->num, &msg, MSG_PEEK);
    if (n <= 0) {
        if ((n < 0) && (get_last_socket_error() != EAGAIN)
            && (get_last_socket_error() != EWOULDBLOCK))
            return -1;
        else
            return 0;
    }

    /* if we find a notification, process it and try again if necessary */
    while (msg.msg_flags & MSG_NOTIFICATION) {
        memset(&snp, 0, sizeof(snp));
        iov.iov_base = (char *)&snp;
        iov.iov_len = sizeof(union sctp_notification);
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        msg.msg_flags = 0;

        n = recvmsg(b->num, &msg, 0);
        if (n <= 0) {
            if ((n < 0) && (get_last_socket_error() != EAGAIN)
                && (get_last_socket_error() != EWOULDBLOCK))
                return -1;
            else
                return is_dry;
        }

        if (snp.sn_header.sn_type == SCTP_SENDER_DRY_EVENT) {
            is_dry = 1;

            /* disable sender dry event */
#  ifdef SCTP_EVENT
            memset(&event, 0, sizeof(event));
            event.se_assoc_id = 0;
            event.se_type = SCTP_SENDER_DRY_EVENT;
            event.se_on = 0;
            ret =
                setsockopt(b->num, IPPROTO_SCTP, SCTP_EVENT, &event,
                           sizeof(struct sctp_event));
#  else
            eventsize = (socklen_t) sizeof(struct sctp_event_subscribe);
            ret =
                getsockopt(b->num, IPPROTO_SCTP, SCTP_EVENTS, &event,
                           &eventsize);
            if (ret < 0)
                return -1;

            event.sctp_sender_dry_event = 0;

            ret =
                setsockopt(b->num, IPPROTO_SCTP, SCTP_EVENTS, &event,
                           sizeof(struct sctp_event_subscribe));
#  endif
            if (ret < 0)
                return -1;
        }
#  ifdef SCTP_AUTHENTICATION_EVENT
        if (snp.sn_header.sn_type == SCTP_AUTHENTICATION_EVENT)
            dgram_sctp_handle_auth_free_key_event(b, &snp);
#  endif

        if (data->handle_notifications != NULL)
            data->handle_notifications(b, data->notification_context,
                                       (void *)&snp);

        /* found notification, peek again */
        memset(&snp, 0, sizeof(snp));
        iov.iov_base = (char *)&snp;
        iov.iov_len = sizeof(union sctp_notification);
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        msg.msg_flags = 0;

        /* if we have seen the dry already, don't wait */
        if (is_dry) {
            sockflags = fcntl(b->num, F_GETFL, 0);
            fcntl(b->num, F_SETFL, O_NONBLOCK);
        }

        n = recvmsg(b->num, &msg, MSG_PEEK);

        if (is_dry) {
            fcntl(b->num, F_SETFL, sockflags);
        }

        if (n <= 0) {
            if ((n < 0) && (get_last_socket_error() != EAGAIN)
                && (get_last_socket_error() != EWOULDBLOCK))
                return -1;
            else
                return is_dry;
        }
    }

    /* read anything else */
    return is_dry;
}