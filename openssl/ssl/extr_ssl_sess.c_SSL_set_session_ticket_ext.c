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
struct TYPE_9__ {int length; struct TYPE_9__* data; } ;
struct TYPE_7__ {TYPE_3__* session_ticket; } ;
struct TYPE_8__ {scalar_t__ version; TYPE_1__ ext; } ;
typedef  int /*<<< orphan*/  TLS_SESSION_TICKET_EXT ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_3__*) ; 
 TYPE_3__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  SSL_F_SSL_SET_SESSION_TICKET_EXT ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLS1_VERSION ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,void*,int) ; 

int SSL_set_session_ticket_ext(SSL *s, void *ext_data, int ext_len)
{
    if (s->version >= TLS1_VERSION) {
        OPENSSL_free(s->ext.session_ticket);
        s->ext.session_ticket = NULL;
        s->ext.session_ticket =
            OPENSSL_malloc(sizeof(TLS_SESSION_TICKET_EXT) + ext_len);
        if (s->ext.session_ticket == NULL) {
            SSLerr(SSL_F_SSL_SET_SESSION_TICKET_EXT, ERR_R_MALLOC_FAILURE);
            return 0;
        }

        if (ext_data != NULL) {
            s->ext.session_ticket->length = ext_len;
            s->ext.session_ticket->data = s->ext.session_ticket + 1;
            memcpy(s->ext.session_ticket->data, ext_data, ext_len);
        } else {
            s->ext.session_ticket->length = 0;
            s->ext.session_ticket->data = NULL;
        }

        return 1;
    }

    return 0;
}