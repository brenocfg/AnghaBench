#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct trace_data_st {int category; void* data; int /*<<< orphan*/ * callback; } ;
typedef  int /*<<< orphan*/ * OSSL_trace_cb ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,struct trace_data_st*) ; 
 int /*<<< orphan*/  CALLBACK_CHANNEL ; 
 int /*<<< orphan*/  OPENSSL_free (struct trace_data_st*) ; 
 struct trace_data_st* OPENSSL_zalloc (int) ; 
 int OSSL_TRACE_CATEGORY_NUM ; 
 int /*<<< orphan*/  set_trace_data (int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_attach_w_callback_cb ; 
 int /*<<< orphan*/  trace_detach_cb ; 
 int /*<<< orphan*/  trace_method ; 

int OSSL_trace_set_callback(int category, OSSL_trace_cb callback, void *data)
{
#ifndef OPENSSL_NO_TRACE
    BIO *channel = NULL;
    struct trace_data_st *trace_data = NULL;

    if (category < 0 || category >= OSSL_TRACE_CATEGORY_NUM)
        return 0;

    if (callback != NULL) {
        if ((channel = BIO_new(&trace_method)) == NULL
            || (trace_data =
                OPENSSL_zalloc(sizeof(struct trace_data_st))) == NULL)
            goto err;

        trace_data->callback = callback;
        trace_data->category = category;
        trace_data->data = data;

        BIO_set_data(channel, trace_data);
    }

    if (!set_trace_data(category, CALLBACK_CHANNEL, &channel, NULL, NULL,
                        trace_attach_w_callback_cb, trace_detach_cb))
        goto err;

    return 1;

 err:
    BIO_free(channel);
    OPENSSL_free(trace_data);
#endif

    return 0;
}