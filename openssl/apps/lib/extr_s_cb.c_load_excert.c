#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  chain; int /*<<< orphan*/ * chainfile; int /*<<< orphan*/ * key; int /*<<< orphan*/  certform; int /*<<< orphan*/ * certfile; int /*<<< orphan*/  keyform; int /*<<< orphan*/ * keyfile; int /*<<< orphan*/ * cert; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SSL_EXCERT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FORMAT_PEM ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * load_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  load_certs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 void* load_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ssl_excert_free (TYPE_1__*) ; 

int load_excert(SSL_EXCERT **pexc)
{
    SSL_EXCERT *exc = *pexc;
    if (exc == NULL)
        return 1;
    /* If nothing in list, free and set to NULL */
    if (exc->certfile == NULL && exc->next == NULL) {
        ssl_excert_free(exc);
        *pexc = NULL;
        return 1;
    }
    for (; exc; exc = exc->next) {
        if (exc->certfile == NULL) {
            BIO_printf(bio_err, "Missing filename\n");
            return 0;
        }
        exc->cert = load_cert(exc->certfile, exc->certform,
                              "Server Certificate");
        if (exc->cert == NULL)
            return 0;
        if (exc->keyfile != NULL) {
            exc->key = load_key(exc->keyfile, exc->keyform,
                                0, NULL, NULL, "Server Key");
        } else {
            exc->key = load_key(exc->certfile, exc->certform,
                                0, NULL, NULL, "Server Key");
        }
        if (exc->key == NULL)
            return 0;
        if (exc->chainfile != NULL) {
            if (!load_certs(exc->chainfile, &exc->chain, FORMAT_PEM, NULL,
                            "Server Chain"))
                return 0;
        }
    }
    return 1;
}