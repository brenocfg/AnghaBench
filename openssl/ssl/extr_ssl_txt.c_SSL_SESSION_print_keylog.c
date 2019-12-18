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
struct TYPE_3__ {size_t session_id_length; size_t master_key_length; int /*<<< orphan*/ * master_key; int /*<<< orphan*/ * session_id; } ;
typedef  TYPE_1__ SSL_SESSION ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 

int SSL_SESSION_print_keylog(BIO *bp, const SSL_SESSION *x)
{
    size_t i;

    if (x == NULL)
        goto err;
    if (x->session_id_length == 0 || x->master_key_length == 0)
        goto err;

    /*
     * the RSA prefix is required by the format's definition although there's
     * nothing RSA-specific in the output, therefore, we don't have to check if
     * the cipher suite is based on RSA
     */
    if (BIO_puts(bp, "RSA ") <= 0)
        goto err;

    if (BIO_puts(bp, "Session-ID:") <= 0)
        goto err;
    for (i = 0; i < x->session_id_length; i++) {
        if (BIO_printf(bp, "%02X", x->session_id[i]) <= 0)
            goto err;
    }
    if (BIO_puts(bp, " Master-Key:") <= 0)
        goto err;
    for (i = 0; i < x->master_key_length; i++) {
        if (BIO_printf(bp, "%02X", x->master_key[i]) <= 0)
            goto err;
    }
    if (BIO_puts(bp, "\n") <= 0)
        goto err;

    return 1;
 err:
    return 0;
}