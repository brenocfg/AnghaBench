#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long inh_flags; int flags; int /*<<< orphan*/  iplen; int /*<<< orphan*/  ip; int /*<<< orphan*/  emaillen; int /*<<< orphan*/  email; int /*<<< orphan*/  hostflags; int /*<<< orphan*/ * hosts; int /*<<< orphan*/  policies; int /*<<< orphan*/  check_time; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;

/* Variables and functions */
 int X509_TRUST_DEFAULT ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_email (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_ip (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_policies (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned long X509_VP_FLAG_DEFAULT ; 
 unsigned long X509_VP_FLAG_LOCKED ; 
 unsigned long X509_VP_FLAG_ONCE ; 
 unsigned long X509_VP_FLAG_OVERWRITE ; 
 unsigned long X509_VP_FLAG_RESET_FLAGS ; 
 int X509_V_FLAG_USE_CHECK_TIME ; 
 int /*<<< orphan*/  auth_level ; 
 int /*<<< orphan*/  depth ; 
 int /*<<< orphan*/  email ; 
 int /*<<< orphan*/  hosts ; 
 int /*<<< orphan*/  ip ; 
 int /*<<< orphan*/  policies ; 
 int /*<<< orphan*/  purpose ; 
 int /*<<< orphan*/ * sk_OPENSSL_STRING_deep_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_copy ; 
 int /*<<< orphan*/  str_free ; 
 scalar_t__ test_x509_verify_param_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trust ; 
 int /*<<< orphan*/  x509_verify_param_copy (int /*<<< orphan*/ ,int) ; 

int X509_VERIFY_PARAM_inherit(X509_VERIFY_PARAM *dest,
                              const X509_VERIFY_PARAM *src)
{
    unsigned long inh_flags;
    int to_default, to_overwrite;
    if (!src)
        return 1;
    inh_flags = dest->inh_flags | src->inh_flags;

    if (inh_flags & X509_VP_FLAG_ONCE)
        dest->inh_flags = 0;

    if (inh_flags & X509_VP_FLAG_LOCKED)
        return 1;

    if (inh_flags & X509_VP_FLAG_DEFAULT)
        to_default = 1;
    else
        to_default = 0;

    if (inh_flags & X509_VP_FLAG_OVERWRITE)
        to_overwrite = 1;
    else
        to_overwrite = 0;

    x509_verify_param_copy(purpose, 0);
    x509_verify_param_copy(trust, X509_TRUST_DEFAULT);
    x509_verify_param_copy(depth, -1);
    x509_verify_param_copy(auth_level, -1);

    /* If overwrite or check time not set, copy across */

    if (to_overwrite || !(dest->flags & X509_V_FLAG_USE_CHECK_TIME)) {
        dest->check_time = src->check_time;
        dest->flags &= ~X509_V_FLAG_USE_CHECK_TIME;
        /* Don't need to copy flag: that is done below */
    }

    if (inh_flags & X509_VP_FLAG_RESET_FLAGS)
        dest->flags = 0;

    dest->flags |= src->flags;

    if (test_x509_verify_param_copy(policies, NULL)) {
        if (!X509_VERIFY_PARAM_set1_policies(dest, src->policies))
            return 0;
    }

    /* Copy the host flags if and only if we're copying the host list */
    if (test_x509_verify_param_copy(hosts, NULL)) {
        sk_OPENSSL_STRING_pop_free(dest->hosts, str_free);
        dest->hosts = NULL;
        if (src->hosts) {
            dest->hosts =
                sk_OPENSSL_STRING_deep_copy(src->hosts, str_copy, str_free);
            if (dest->hosts == NULL)
                return 0;
            dest->hostflags = src->hostflags;
        }
    }

    if (test_x509_verify_param_copy(email, NULL)) {
        if (!X509_VERIFY_PARAM_set1_email(dest, src->email, src->emaillen))
            return 0;
    }

    if (test_x509_verify_param_copy(ip, NULL)) {
        if (!X509_VERIFY_PARAM_set1_ip(dest, src->ip, src->iplen))
            return 0;
    }

    return 1;
}