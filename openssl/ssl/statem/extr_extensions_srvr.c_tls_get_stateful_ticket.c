#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ticket_expected; } ;
struct TYPE_6__ {TYPE_1__ ext; } ;
typedef  int /*<<< orphan*/  SSL_TICKET_STATUS ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int PACKET_remaining (int /*<<< orphan*/ *) ; 
#define  SSL_MAX_SSL_SESSION_ID_LENGTH 128 
 int /*<<< orphan*/  SSL_TICKET_EMPTY ; 
 int /*<<< orphan*/  SSL_TICKET_NO_DECRYPT ; 
 int /*<<< orphan*/  SSL_TICKET_SUCCESS ; 
 int /*<<< orphan*/ * lookup_sess_in_cache (TYPE_2__*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static SSL_TICKET_STATUS tls_get_stateful_ticket(SSL *s, PACKET *tick,
                                                 SSL_SESSION **sess)
{
    SSL_SESSION *tmpsess = NULL;

    s->ext.ticket_expected = 1;

    switch (PACKET_remaining(tick)) {
        case 0:
            return SSL_TICKET_EMPTY;

        case SSL_MAX_SSL_SESSION_ID_LENGTH:
            break;

        default:
            return SSL_TICKET_NO_DECRYPT;
    }

    tmpsess = lookup_sess_in_cache(s, PACKET_data(tick),
                                   SSL_MAX_SSL_SESSION_ID_LENGTH);

    if (tmpsess == NULL)
        return SSL_TICKET_NO_DECRYPT;

    *sess = tmpsess;
    return SSL_TICKET_SUCCESS;
}