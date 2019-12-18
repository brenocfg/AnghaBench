#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* ticket_cb_data; int /*<<< orphan*/  decrypt_ticket_cb; int /*<<< orphan*/  generate_ticket_cb; } ;
typedef  int /*<<< orphan*/  SSL_CTX_generate_session_ticket_fn ;
typedef  int /*<<< orphan*/  SSL_CTX_decrypt_session_ticket_fn ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */

int SSL_CTX_set_session_ticket_cb(SSL_CTX *ctx,
                                  SSL_CTX_generate_session_ticket_fn gen_cb,
                                  SSL_CTX_decrypt_session_ticket_fn dec_cb,
                                  void *arg)
{
    ctx->generate_ticket_cb = gen_cb;
    ctx->decrypt_ticket_cb = dec_cb;
    ctx->ticket_cb_data = arg;
    return 1;
}