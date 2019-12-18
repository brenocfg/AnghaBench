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
struct TYPE_6__ {int /*<<< orphan*/  rlayer; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ SSL3_BUFFER ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* RECORD_LAYER_get_rbuf (int /*<<< orphan*/ *) ; 

int ssl3_release_read_buffer(SSL *s)
{
    SSL3_BUFFER *b;

    b = RECORD_LAYER_get_rbuf(&s->rlayer);
    OPENSSL_free(b->buf);
    b->buf = NULL;
    return 1;
}