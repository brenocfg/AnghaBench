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
union sctp_notification {TYPE_1__ sn_header; } ;
struct msghdr {int msg_flags; int msg_iovlen; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  snp ;
struct TYPE_8__ {int /*<<< orphan*/  notification_context; int /*<<< orphan*/  (* handle_notifications ) (TYPE_3__*,int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_2__ bio_dgram_sctp_data ;
struct TYPE_9__ {int /*<<< orphan*/  num; scalar_t__ ptr; } ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int MSG_NOTIFICATION ; 
 int /*<<< orphan*/  MSG_PEEK ; 
 int O_NONBLOCK ; 
 scalar_t__ SCTP_AUTHENTICATION_EVENT ; 
 int /*<<< orphan*/  dgram_sctp_handle_auth_free_key_event (TYPE_3__*,union sctp_notification*) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union sctp_notification*,int /*<<< orphan*/ ,int) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int dgram_sctp_msg_waiting(BIO *b)
{
    int n, sockflags;
    union sctp_notification snp;
    struct msghdr msg;
    struct iovec iov;
    bio_dgram_sctp_data *data = (bio_dgram_sctp_data *) b->ptr;

    /* Check if there are any messages waiting to be read */
    do {
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

        sockflags = fcntl(b->num, F_GETFL, 0);
        fcntl(b->num, F_SETFL, O_NONBLOCK);
        n = recvmsg(b->num, &msg, MSG_PEEK);
        fcntl(b->num, F_SETFL, sockflags);

        /* if notification, process and try again */
        if (n > 0 && (msg.msg_flags & MSG_NOTIFICATION)) {
#  ifdef SCTP_AUTHENTICATION_EVENT
            if (snp.sn_header.sn_type == SCTP_AUTHENTICATION_EVENT)
                dgram_sctp_handle_auth_free_key_event(b, &snp);
#  endif

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

            if (data->handle_notifications != NULL)
                data->handle_notifications(b, data->notification_context,
                                           (void *)&snp);
        }

    } while (n > 0 && (msg.msg_flags & MSG_NOTIFICATION));

    /* Return 1 if there is a message to be read, return 0 otherwise. */
    if (n > 0)
        return 1;
    else
        return 0;
}