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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_BIND_REUSEADDR ; 
 scalar_t__ BIO_do_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_f_buffer () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_s_accept () ; 
 int /*<<< orphan*/  BIO_set_accept_bios (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_set_accept_port (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ BIO_set_bind_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  log_message (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static BIO *init_responder(const char *port)
{
# ifdef OPENSSL_NO_SOCK
    BIO_printf(bio_err,
               "Error setting up accept BIO - sockets not supported.\n");
    return NULL;
# else
    BIO *acbio = NULL, *bufbio = NULL;

    bufbio = BIO_new(BIO_f_buffer());
    if (bufbio == NULL)
        goto err;
    acbio = BIO_new(BIO_s_accept());
    if (acbio == NULL
        || BIO_set_bind_mode(acbio, BIO_BIND_REUSEADDR) < 0
        || BIO_set_accept_port(acbio, port) < 0) {
        log_message(LOG_ERR, "Error setting up accept BIO");
        goto err;
    }

    BIO_set_accept_bios(acbio, bufbio);
    bufbio = NULL;
    if (BIO_do_accept(acbio) <= 0) {
        log_message(LOG_ERR, "Error starting accept");
        goto err;
    }

    return acbio;

 err:
    BIO_free_all(acbio);
    BIO_free(bufbio);
    return NULL;
# endif
}