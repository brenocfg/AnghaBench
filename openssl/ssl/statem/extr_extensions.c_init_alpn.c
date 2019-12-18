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
struct TYPE_4__ {scalar_t__ alpn_proposed_len; int /*<<< orphan*/ * alpn_proposed; scalar_t__ alpn_selected_len; int /*<<< orphan*/ * alpn_selected; } ;
struct TYPE_5__ {TYPE_1__ s3; scalar_t__ server; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_alpn(SSL *s, unsigned int context)
{
    OPENSSL_free(s->s3.alpn_selected);
    s->s3.alpn_selected = NULL;
    s->s3.alpn_selected_len = 0;
    if (s->server) {
        OPENSSL_free(s->s3.alpn_proposed);
        s->s3.alpn_proposed = NULL;
        s->s3.alpn_proposed_len = 0;
    }
    return 1;
}