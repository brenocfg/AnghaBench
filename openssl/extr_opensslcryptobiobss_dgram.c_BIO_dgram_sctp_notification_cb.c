#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void (* handle_notifications ) (TYPE_1__*,void*,void*) ;void* notification_context; } ;
typedef  TYPE_2__ bio_dgram_sctp_data ;
struct TYPE_6__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */

int BIO_dgram_sctp_notification_cb(BIO *b,
                                   void (*handle_notifications) (BIO *bio,
                                                                 void
                                                                 *context,
                                                                 void *buf),
                                   void *context)
{
    bio_dgram_sctp_data *data = (bio_dgram_sctp_data *) b->ptr;

    if (handle_notifications != NULL) {
        data->handle_notifications = handle_notifications;
        data->notification_context = context;
    } else
        return -1;

    return 0;
}