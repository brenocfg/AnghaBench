#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int version; TYPE_3__* (* cmeth ) () ;} ;
typedef  TYPE_2__ version_info ;
struct TYPE_14__ {int version; TYPE_1__* method; } ;
struct TYPE_13__ {int version; } ;
struct TYPE_11__ {int version; } ;
typedef  TYPE_3__ SSL_METHOD ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
#define  DTLS_ANY_VERSION 129 
 int ERR_R_INTERNAL_ERROR ; 
 int SSL_R_NO_PROTOCOLS_AVAILABLE ; 
#define  TLS_ANY_VERSION 128 
 TYPE_2__* dtls_version_table ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ssl_method_error (TYPE_4__ const*,TYPE_3__ const*) ; 
 TYPE_3__* stub1 () ; 
 TYPE_2__* tls_version_table ; 

int ssl_get_min_max_version(const SSL *s, int *min_version, int *max_version,
                            int *real_max)
{
    int version, tmp_real_max;
    int hole;
    const SSL_METHOD *single = NULL;
    const SSL_METHOD *method;
    const version_info *table;
    const version_info *vent;

    switch (s->method->version) {
    default:
        /*
         * If this SSL handle is not from a version flexible method we don't
         * (and never did) check min/max FIPS or Suite B constraints.  Hope
         * that's OK.  It is up to the caller to not choose fixed protocol
         * versions they don't want.  If not, then easy to fix, just return
         * ssl_method_error(s, s->method)
         */
        *min_version = *max_version = s->version;
        /*
         * Providing a real_max only makes sense where we're using a version
         * flexible method.
         */
        if (!ossl_assert(real_max == NULL))
            return ERR_R_INTERNAL_ERROR;
        return 0;
    case TLS_ANY_VERSION:
        table = tls_version_table;
        break;
    case DTLS_ANY_VERSION:
        table = dtls_version_table;
        break;
    }

    /*
     * SSL_OP_NO_X disables all protocols above X *if* there are some protocols
     * below X enabled. This is required in order to maintain the "version
     * capability" vector contiguous. Any versions with a NULL client method
     * (protocol version client is disabled at compile-time) is also a "hole".
     *
     * Our initial state is hole == 1, version == 0.  That is, versions above
     * the first version in the method table are disabled (a "hole" above
     * the valid protocol entries) and we don't have a selected version yet.
     *
     * Whenever "hole == 1", and we hit an enabled method, its version becomes
     * the selected version, and the method becomes a candidate "single"
     * method.  We're no longer in a hole, so "hole" becomes 0.
     *
     * If "hole == 0" and we hit an enabled method, then "single" is cleared,
     * as we support a contiguous range of at least two methods.  If we hit
     * a disabled method, then hole becomes true again, but nothing else
     * changes yet, because all the remaining methods may be disabled too.
     * If we again hit an enabled method after the new hole, it becomes
     * selected, as we start from scratch.
     */
    *min_version = version = 0;
    hole = 1;
    if (real_max != NULL)
        *real_max = 0;
    tmp_real_max = 0;
    for (vent = table; vent->version != 0; ++vent) {
        /*
         * A table entry with a NULL client method is still a hole in the
         * "version capability" vector.
         */
        if (vent->cmeth == NULL) {
            hole = 1;
            tmp_real_max = 0;
            continue;
        }
        method = vent->cmeth();

        if (hole == 1 && tmp_real_max == 0)
            tmp_real_max = vent->version;

        if (ssl_method_error(s, method) != 0) {
            hole = 1;
        } else if (!hole) {
            single = NULL;
            *min_version = method->version;
        } else {
            if (real_max != NULL && tmp_real_max != 0)
                *real_max = tmp_real_max;
            version = (single = method)->version;
            *min_version = version;
            hole = 0;
        }
    }

    *max_version = version;

    /* Fail if everything is disabled */
    if (version == 0)
        return SSL_R_NO_PROTOCOLS_AVAILABLE;

    return 0;
}