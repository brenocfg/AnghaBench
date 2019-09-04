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
struct TYPE_7__ {TYPE_1__* d1; } ;
struct TYPE_6__ {int timeout_duration_us; int /*<<< orphan*/  next_timeout; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_DGRAM_SET_NEXT_TIMEOUT ; 
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_rbio (TYPE_2__*) ; 
 int /*<<< orphan*/  dtls1_clear_sent_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void dtls1_stop_timer(SSL *s)
{
    /* Reset everything */
    memset(&s->d1->timeout, 0, sizeof(s->d1->timeout));
    memset(&s->d1->next_timeout, 0, sizeof(s->d1->next_timeout));
    s->d1->timeout_duration_us = 1000000;
    BIO_ctrl(SSL_get_rbio(s), BIO_CTRL_DGRAM_SET_NEXT_TIMEOUT, 0,
             &(s->d1->next_timeout));
    /* Clear retransmission buffer */
    dtls1_clear_sent_buffer(s);
}