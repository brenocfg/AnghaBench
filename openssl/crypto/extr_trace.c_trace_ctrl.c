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
struct trace_data_st {int /*<<< orphan*/  data; int /*<<< orphan*/  category; int /*<<< orphan*/  (* callback ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 struct trace_data_st* BIO_get_data (int /*<<< orphan*/ *) ; 
#define  OSSL_TRACE_CTRL_BEGIN 129 
#define  OSSL_TRACE_CTRL_END 128 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long trace_ctrl(BIO *channel, int cmd, long argl, void *argp)
{
    struct trace_data_st *ctx = BIO_get_data(channel);

    switch (cmd) {
    case OSSL_TRACE_CTRL_BEGIN:
    case OSSL_TRACE_CTRL_END:
        /* We know that the callback is likely to return 0 here */
        ctx->callback("", 0, ctx->category, cmd, ctx->data);
        return 1;
    default:
        break;
    }
    return -2;                   /* Unsupported */
}