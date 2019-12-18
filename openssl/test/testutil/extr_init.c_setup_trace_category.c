#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * bio; } ;
typedef  TYPE_1__ tracedata ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_FP_TEXT ; 
 int BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_new_fp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 scalar_t__ OSSL_trace_enabled (int) ; 
 char* OSSL_trace_get_category_name (int) ; 
 scalar_t__ OSSL_trace_set_callback (int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  apps_bf_prefix () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * internal_trace_cb ; 
 scalar_t__ sk_tracedata_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  trace_data_stack ; 

__attribute__((used)) static void setup_trace_category(int category)
{
    BIO *channel;
    tracedata *trace_data;

    if (OSSL_trace_enabled(category))
        return;

    channel = BIO_push(BIO_new(apps_bf_prefix()),
                       BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT));
    trace_data = OPENSSL_zalloc(sizeof(*trace_data));

    if (trace_data == NULL
        || (trace_data->bio = channel) == NULL
        || OSSL_trace_set_callback(category, internal_trace_cb,
                                   trace_data) == 0
        || sk_tracedata_push(trace_data_stack, trace_data) == 0) {

        fprintf(stderr,
                "warning: unable to setup trace callback for category '%s'.\n",
                OSSL_trace_get_category_name(category));

        OSSL_trace_set_callback(category, NULL, NULL);
        BIO_free_all(channel);
    }
}