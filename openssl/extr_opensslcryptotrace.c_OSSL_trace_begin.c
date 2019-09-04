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
struct TYPE_2__ {char* prefix; int type; int /*<<< orphan*/ * bio; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
#define  CALLBACK_CHANNEL 129 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_TRACE_CTRL_BEGIN ; 
#define  SIMPLE_CHANNEL 128 
 int /*<<< orphan*/ * current_channel ; 
 int ossl_trace_get_category (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* trace_channels ; 
 int /*<<< orphan*/  trace_lock ; 

BIO *OSSL_trace_begin(int category)
{
    BIO *channel = NULL;
#ifndef OPENSSL_NO_TRACE
    char *prefix = NULL;

    category = ossl_trace_get_category(category);
    if (category < 0)
        return NULL;

    channel = trace_channels[category].bio;
    prefix = trace_channels[category].prefix;

    if (channel != NULL) {
        CRYPTO_THREAD_write_lock(trace_lock);
        current_channel = channel;
        switch (trace_channels[category].type) {
        case SIMPLE_CHANNEL:
            if (prefix != NULL) {
                (void)BIO_puts(channel, prefix);
                (void)BIO_puts(channel, "\n");
            }
            break;
        case CALLBACK_CHANNEL:
            (void)BIO_ctrl(channel, OSSL_TRACE_CTRL_BEGIN,
                           prefix == NULL ? 0 : strlen(prefix), prefix);
            break;
        }
    }
#endif
    return channel;
}