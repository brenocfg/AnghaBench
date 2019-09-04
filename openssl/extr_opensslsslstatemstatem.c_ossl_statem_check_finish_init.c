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
struct TYPE_5__ {scalar_t__ hand_state; } ;
struct TYPE_6__ {scalar_t__ early_data_state; TYPE_1__ statem; int /*<<< orphan*/  server; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 scalar_t__ SSL_EARLY_DATA_FINISHED_READING ; 
 void* SSL_EARLY_DATA_FINISHED_WRITING ; 
 scalar_t__ SSL_EARLY_DATA_WRITE_RETRY ; 
 scalar_t__ SSL_EARLY_DATA_WRITING ; 
 scalar_t__ TLS_ST_EARLY_DATA ; 
 scalar_t__ TLS_ST_PENDING_EARLY_DATA_END ; 
 int /*<<< orphan*/  ossl_statem_set_in_init (TYPE_2__*,int) ; 

void ossl_statem_check_finish_init(SSL *s, int sending)
{
    if (sending == -1) {
        if (s->statem.hand_state == TLS_ST_PENDING_EARLY_DATA_END
                || s->statem.hand_state == TLS_ST_EARLY_DATA) {
            ossl_statem_set_in_init(s, 1);
            if (s->early_data_state == SSL_EARLY_DATA_WRITE_RETRY) {
                /*
                 * SSL_connect() or SSL_do_handshake() has been called directly.
                 * We don't allow any more writing of early data.
                 */
                s->early_data_state = SSL_EARLY_DATA_FINISHED_WRITING;
            }
        }
    } else if (!s->server) {
        if ((sending && (s->statem.hand_state == TLS_ST_PENDING_EARLY_DATA_END
                      || s->statem.hand_state == TLS_ST_EARLY_DATA)
                  && s->early_data_state != SSL_EARLY_DATA_WRITING)
                || (!sending && s->statem.hand_state == TLS_ST_EARLY_DATA)) {
            ossl_statem_set_in_init(s, 1);
            /*
             * SSL_write() has been called directly. We don't allow any more
             * writing of early data.
             */
            if (sending && s->early_data_state == SSL_EARLY_DATA_WRITE_RETRY)
                s->early_data_state = SSL_EARLY_DATA_FINISHED_WRITING;
        }
    } else {
        if (s->early_data_state == SSL_EARLY_DATA_FINISHED_READING
                && s->statem.hand_state == TLS_ST_EARLY_DATA)
            ossl_statem_set_in_init(s, 1);
    }
}