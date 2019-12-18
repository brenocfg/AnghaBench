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
struct TYPE_3__ {unsigned char* der; int /*<<< orphan*/  derlen; int /*<<< orphan*/  id; scalar_t__ idlen; struct TYPE_3__* next; } ;
typedef  TYPE_1__ simple_ssl_session ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * d2i_SSL_SESSION (int /*<<< orphan*/ *,unsigned char const**,int /*<<< orphan*/ ) ; 
 TYPE_1__* first ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static SSL_SESSION *get_session(SSL *ssl, const unsigned char *id, int idlen,
                                int *do_copy)
{
    simple_ssl_session *sess;
    *do_copy = 0;
    for (sess = first; sess; sess = sess->next) {
        if (idlen == (int)sess->idlen && !memcmp(sess->id, id, idlen)) {
            const unsigned char *p = sess->der;
            BIO_printf(bio_err, "Lookup session: cache hit\n");
            return d2i_SSL_SESSION(NULL, &p, sess->derlen);
        }
    }
    BIO_printf(bio_err, "Lookup session: cache miss\n");
    return NULL;
}