#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  write_hash; int /*<<< orphan*/  enc_write_ctx; } ;
struct TYPE_7__ {TYPE_1__ saved_retransmit_state; scalar_t__ is_ccs; } ;
struct TYPE_8__ {struct TYPE_8__* reassembly; struct TYPE_8__* fragment; TYPE_2__ msg_header; } ;
typedef  TYPE_3__ hm_fragment ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_3__*) ; 

void dtls1_hm_fragment_free(hm_fragment *frag)
{
    if (!frag)
        return;
    if (frag->msg_header.is_ccs) {
        EVP_CIPHER_CTX_free(frag->msg_header.
                            saved_retransmit_state.enc_write_ctx);
        EVP_MD_CTX_free(frag->msg_header.saved_retransmit_state.write_hash);
    }
    OPENSSL_free(frag->fragment);
    OPENSSL_free(frag->reassembly);
    OPENSSL_free(frag);
}