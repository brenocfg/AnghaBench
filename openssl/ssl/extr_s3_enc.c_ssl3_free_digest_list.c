#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * handshake_dgst; int /*<<< orphan*/ * handshake_buffer; } ;
struct TYPE_5__ {TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 

void ssl3_free_digest_list(SSL *s)
{
    BIO_free(s->s3.handshake_buffer);
    s->s3.handshake_buffer = NULL;
    EVP_MD_CTX_free(s->s3.handshake_dgst);
    s->s3.handshake_dgst = NULL;
}