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
struct TYPE_3__ {int /*<<< orphan*/ * hosts; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strndup (char const*,size_t) ; 
 int SET_HOST ; 
 scalar_t__ memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_OPENSSL_STRING_new_null () ; 
 scalar_t__ sk_OPENSSL_STRING_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  str_free ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int int_x509_param_set_hosts(X509_VERIFY_PARAM *vpm, int mode,
                                    const char *name, size_t namelen)
{
    char *copy;

    /*
     * Refuse names with embedded NUL bytes, except perhaps as final byte.
     * XXX: Do we need to push an error onto the error stack?
     */
    if (namelen == 0 || name == NULL)
        namelen = name ? strlen(name) : 0;
    else if (name && memchr(name, '\0', namelen > 1 ? namelen - 1 : namelen))
        return 0;
    if (namelen > 0 && name[namelen - 1] == '\0')
        --namelen;

    if (mode == SET_HOST) {
        sk_OPENSSL_STRING_pop_free(vpm->hosts, str_free);
        vpm->hosts = NULL;
    }
    if (name == NULL || namelen == 0)
        return 1;

    copy = OPENSSL_strndup(name, namelen);
    if (copy == NULL)
        return 0;

    if (vpm->hosts == NULL &&
        (vpm->hosts = sk_OPENSSL_STRING_new_null()) == NULL) {
        OPENSSL_free(copy);
        return 0;
    }

    if (!sk_OPENSSL_STRING_push(vpm->hosts, copy)) {
        OPENSSL_free(copy);
        if (sk_OPENSSL_STRING_num(vpm->hosts) == 0) {
            sk_OPENSSL_STRING_free(vpm->hosts);
            vpm->hosts = NULL;
        }
        return 0;
    }

    return 1;
}