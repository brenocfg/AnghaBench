#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {size_t supportedgroups_len; int /*<<< orphan*/ * supportedgroups; } ;
struct TYPE_6__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 size_t OSSL_NELEM (int /*<<< orphan*/ *) ; 
#define  SSL_CERT_FLAG_SUITEB_128_LOS 130 
#define  SSL_CERT_FLAG_SUITEB_128_LOS_ONLY 129 
#define  SSL_CERT_FLAG_SUITEB_192_LOS 128 
 int /*<<< orphan*/ * suiteb_curves ; 
 int /*<<< orphan*/ * supported_groups_default ; 
 int tls1_suiteb (TYPE_2__*) ; 

void tls1_get_supported_groups(SSL *s, const uint16_t **pgroups,
                               size_t *pgroupslen)
{
#if !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH)
    /* For Suite B mode only include P-256, P-384 */
    switch (tls1_suiteb(s)) {
# ifndef OPENSSL_NO_EC
    case SSL_CERT_FLAG_SUITEB_128_LOS:
        *pgroups = suiteb_curves;
        *pgroupslen = OSSL_NELEM(suiteb_curves);
        break;

    case SSL_CERT_FLAG_SUITEB_128_LOS_ONLY:
        *pgroups = suiteb_curves;
        *pgroupslen = 1;
        break;

    case SSL_CERT_FLAG_SUITEB_192_LOS:
        *pgroups = suiteb_curves + 1;
        *pgroupslen = 1;
        break;
# endif

    default:
        if (s->ext.supportedgroups == NULL) {
            *pgroups = supported_groups_default;
            *pgroupslen = OSSL_NELEM(supported_groups_default);
        } else {
            *pgroups = s->ext.supportedgroups;
            *pgroupslen = s->ext.supportedgroups_len;
        }
        break;
    }
#else
    *pgroups = NULL;
    *pgroupslen = 0;
#endif /* !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH) */
}