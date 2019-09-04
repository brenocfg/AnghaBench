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
struct TYPE_3__ {int /*<<< orphan*/  tls13_ciphersuites; int /*<<< orphan*/  cipher_list_by_id; int /*<<< orphan*/ * cipher_list; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int set_ciphersuites (int /*<<< orphan*/ *,char const*) ; 
 int update_cipher_list (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int SSL_set_ciphersuites(SSL *s, const char *str)
{
    int ret = set_ciphersuites(&(s->tls13_ciphersuites), str);

    if (ret && s->cipher_list != NULL) {
        /* We already have a cipher_list, so we need to update it */
        return update_cipher_list(&s->cipher_list, &s->cipher_list_by_id,
                                  s->tls13_ciphersuites);
    }

    return ret;
}