#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* suffix; int type; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
#define  CALLBACK_CHANNEL 129 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_TRACE_CTRL_END ; 
#define  SIMPLE_CHANNEL 128 
 int /*<<< orphan*/ * current_channel ; 
 scalar_t__ ossl_assert (int) ; 
 int ossl_trace_get_category (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* trace_channels ; 
 int /*<<< orphan*/  trace_lock ; 

void OSSL_trace_end(int category, BIO * channel)
{
#ifndef OPENSSL_NO_TRACE
    char *suffix = NULL;

    category = ossl_trace_get_category(category);
    suffix = trace_channels[category].suffix;
    if (channel != NULL
        && ossl_assert(channel == current_channel)) {
        (void)BIO_flush(channel);
        switch (trace_channels[category].type) {
        case SIMPLE_CHANNEL:
            if (suffix != NULL) {
                (void)BIO_puts(channel, suffix);
                (void)BIO_puts(channel, "\n");
            }
            break;
        case CALLBACK_CHANNEL:
            (void)BIO_ctrl(channel, OSSL_TRACE_CTRL_END,
                           suffix == NULL ? 0 : strlen(suffix), suffix);
            break;
        }
        current_channel = NULL;
        CRYPTO_THREAD_unlock(trace_lock);
    }
#endif
}