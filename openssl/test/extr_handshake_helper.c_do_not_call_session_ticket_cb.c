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
struct TYPE_2__ {int session_ticket_do_not_call; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  HMAC_CTX ;
typedef  TYPE_1__ HANDSHAKE_EX_DATA ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ SSL_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_data_idx ; 

__attribute__((used)) static int do_not_call_session_ticket_cb(SSL *s, unsigned char *key_name,
                                         unsigned char *iv,
                                         EVP_CIPHER_CTX *ctx,
                                         HMAC_CTX *hctx, int enc)
{
    HANDSHAKE_EX_DATA *ex_data =
        (HANDSHAKE_EX_DATA*)(SSL_get_ex_data(s, ex_data_idx));
    ex_data->session_ticket_do_not_call = 1;
    return 0;
}