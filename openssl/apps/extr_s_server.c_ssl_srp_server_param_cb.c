#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * login; TYPE_2__* user; } ;
typedef  TYPE_1__ srpsrvparm ;
struct TYPE_4__ {int /*<<< orphan*/  info; int /*<<< orphan*/  v; int /*<<< orphan*/  s; int /*<<< orphan*/  g; int /*<<< orphan*/  N; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  SRP_user_pwd_free (TYPE_2__*) ; 
 int SSL3_AL_FATAL ; 
 int SSL_AD_INTERNAL_ERROR ; 
 int SSL_ERROR_NONE ; 
 int /*<<< orphan*/ * SSL_get_srp_username (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_set_srp_server_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int ssl_srp_server_param_cb(SSL *s, int *ad, void *arg)
{
    srpsrvparm *p = (srpsrvparm *) arg;
    int ret = SSL3_AL_FATAL;

    if (p->login == NULL && p->user == NULL) {
        p->login = SSL_get_srp_username(s);
        BIO_printf(bio_err, "SRP username = \"%s\"\n", p->login);
        return -1;
    }

    if (p->user == NULL) {
        BIO_printf(bio_err, "User %s doesn't exist\n", p->login);
        goto err;
    }

    if (SSL_set_srp_server_param
        (s, p->user->N, p->user->g, p->user->s, p->user->v,
         p->user->info) < 0) {
        *ad = SSL_AD_INTERNAL_ERROR;
        goto err;
    }
    BIO_printf(bio_err,
               "SRP parameters set: username = \"%s\" info=\"%s\" \n",
               p->login, p->user->info);
    ret = SSL_ERROR_NONE;

 err:
    SRP_user_pwd_free(p->user);
    p->user = NULL;
    p->login = NULL;
    return ret;
}