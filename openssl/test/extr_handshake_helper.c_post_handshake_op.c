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
struct TYPE_3__ {int handshake_mode; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;

/* Variables and functions */
#define  SSL_TEST_HANDSHAKE_KEY_UPDATE_CLIENT 130 
#define  SSL_TEST_HANDSHAKE_KEY_UPDATE_SERVER 129 
#define  SSL_TEST_HANDSHAKE_POST_HANDSHAKE_AUTH 128 

__attribute__((used)) static int post_handshake_op(const SSL_TEST_CTX *test_ctx)
{
    switch (test_ctx->handshake_mode) {
    case SSL_TEST_HANDSHAKE_KEY_UPDATE_CLIENT:
    case SSL_TEST_HANDSHAKE_KEY_UPDATE_SERVER:
    case SSL_TEST_HANDSHAKE_POST_HANDSHAKE_AUTH:
        return 1;
    default:
        return 0;
    }
}