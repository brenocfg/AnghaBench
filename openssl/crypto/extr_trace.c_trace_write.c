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
struct trace_data_st {size_t (* callback ) (char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  category; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 struct trace_data_st* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_TRACE_CTRL_WRITE ; 
 size_t stub1 (char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trace_write(BIO *channel,
                       const char *buf, size_t num, size_t *written)
{
    struct trace_data_st *ctx = BIO_get_data(channel);
    size_t cnt = ctx->callback(buf, num, ctx->category, OSSL_TRACE_CTRL_WRITE,
                               ctx->data);

    *written = cnt;
    return cnt != 0;
}