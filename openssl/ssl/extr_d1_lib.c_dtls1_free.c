#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sent_messages; int /*<<< orphan*/  buffered_messages; } ;
struct TYPE_6__ {TYPE_5__* d1; int /*<<< orphan*/  rlayer; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  DTLS_RECORD_LAYER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_5__*) ; 
 int /*<<< orphan*/  dtls1_clear_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  pqueue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_free (TYPE_1__*) ; 

void dtls1_free(SSL *s)
{
    DTLS_RECORD_LAYER_free(&s->rlayer);

    ssl3_free(s);

    dtls1_clear_queues(s);

    pqueue_free(s->d1->buffered_messages);
    pqueue_free(s->d1->sent_messages);

    OPENSSL_free(s->d1);
    s->d1 = NULL;
}