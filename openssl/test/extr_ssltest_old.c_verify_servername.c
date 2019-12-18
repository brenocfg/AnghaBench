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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * SSL_get_SSL_CTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_stdout ; 
 int /*<<< orphan*/ * s_ctx ; 
 int /*<<< orphan*/ * s_ctx2 ; 
 int sn_expect ; 

__attribute__((used)) static int verify_servername(SSL *client, SSL *server)
{
    /* just need to see if sn_context is what we expect */
    SSL_CTX* ctx = SSL_get_SSL_CTX(server);
    if (sn_expect == 0)
        return 0;
    if (sn_expect == 1 && ctx == s_ctx)
        return 0;
    if (sn_expect == 2 && ctx == s_ctx2)
        return 0;
    BIO_printf(bio_stdout, "Servername: expected context %d\n", sn_expect);
    if (ctx == s_ctx2)
        BIO_printf(bio_stdout, "Servername: context is 2\n");
    else if (ctx == s_ctx)
        BIO_printf(bio_stdout, "Servername: context is 1\n");
    else
        BIO_printf(bio_stdout, "Servername: context is unknown\n");
    return -1;
}