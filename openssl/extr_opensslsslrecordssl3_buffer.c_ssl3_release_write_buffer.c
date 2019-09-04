#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t numwpipes; } ;
struct TYPE_7__ {TYPE_5__ rlayer; int /*<<< orphan*/ * wbio; } ;
struct TYPE_6__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ SSL3_BUFFER ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_get_ktls_send (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* RECORD_LAYER_get_wbuf (TYPE_5__*) ; 

int ssl3_release_write_buffer(SSL *s)
{
    SSL3_BUFFER *wb;
    size_t pipes;

    pipes = s->rlayer.numwpipes;
    while (pipes > 0) {
        wb = &RECORD_LAYER_get_wbuf(&s->rlayer)[pipes - 1];

        if (s->wbio == NULL || !BIO_get_ktls_send(s->wbio))
            OPENSSL_free(wb->buf);
        wb->buf = NULL;
        pipes--;
    }
    s->rlayer.numwpipes = 0;
    return 1;
}