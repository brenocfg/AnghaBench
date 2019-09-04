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

/* Variables and functions */
 int DTLS1_2_VERSION ; 
 int DTLS1_BAD_VER ; 
 int DTLS1_VERSION ; 
 int DTLS1_VERSION_MAJOR ; 
 int SSL3_VERSION ; 
 int TLS1_3_VERSION ; 

__attribute__((used)) static int ssl_check_allowed_versions(int min_version, int max_version)
{
    int minisdtls = 0, maxisdtls = 0;

    /* Figure out if we're doing DTLS versions or TLS versions */
    if (min_version == DTLS1_BAD_VER
        || min_version >> 8 == DTLS1_VERSION_MAJOR)
        minisdtls = 1;
    if (max_version == DTLS1_BAD_VER
        || max_version >> 8 == DTLS1_VERSION_MAJOR)
        maxisdtls = 1;
    /* A wildcard version of 0 could be DTLS or TLS. */
    if ((minisdtls && !maxisdtls && max_version != 0)
        || (maxisdtls && !minisdtls && min_version != 0)) {
        /* Mixing DTLS and TLS versions will lead to sadness; deny it. */
        return 0;
    }

    if (minisdtls || maxisdtls) {
        /* Do DTLS version checks. */
        if (min_version == 0)
            /* Ignore DTLS1_BAD_VER */
            min_version = DTLS1_VERSION;
        if (max_version == 0)
            max_version = DTLS1_2_VERSION;
#ifdef OPENSSL_NO_DTLS1_2
        if (max_version == DTLS1_2_VERSION)
            max_version = DTLS1_VERSION;
#endif
#ifdef OPENSSL_NO_DTLS1
        if (min_version == DTLS1_VERSION)
            min_version = DTLS1_2_VERSION;
#endif
        /* Done massaging versions; do the check. */
        if (0
#ifdef OPENSSL_NO_DTLS1
            || (DTLS_VERSION_GE(min_version, DTLS1_VERSION)
                && DTLS_VERSION_GE(DTLS1_VERSION, max_version))
#endif
#ifdef OPENSSL_NO_DTLS1_2
            || (DTLS_VERSION_GE(min_version, DTLS1_2_VERSION)
                && DTLS_VERSION_GE(DTLS1_2_VERSION, max_version))
#endif
            )
            return 0;
    } else {
        /* Regular TLS version checks. */
        if (min_version == 0)
            min_version = SSL3_VERSION;
        if (max_version == 0)
            max_version = TLS1_3_VERSION;
#ifdef OPENSSL_NO_TLS1_3
        if (max_version == TLS1_3_VERSION)
            max_version = TLS1_2_VERSION;
#endif
#ifdef OPENSSL_NO_TLS1_2
        if (max_version == TLS1_2_VERSION)
            max_version = TLS1_1_VERSION;
#endif
#ifdef OPENSSL_NO_TLS1_1
        if (max_version == TLS1_1_VERSION)
            max_version = TLS1_VERSION;
#endif
#ifdef OPENSSL_NO_TLS1
        if (max_version == TLS1_VERSION)
            max_version = SSL3_VERSION;
#endif
#ifdef OPENSSL_NO_SSL3
        if (min_version == SSL3_VERSION)
            min_version = TLS1_VERSION;
#endif
#ifdef OPENSSL_NO_TLS1
        if (min_version == TLS1_VERSION)
            min_version = TLS1_1_VERSION;
#endif
#ifdef OPENSSL_NO_TLS1_1
        if (min_version == TLS1_1_VERSION)
            min_version = TLS1_2_VERSION;
#endif
#ifdef OPENSSL_NO_TLS1_2
        if (min_version == TLS1_2_VERSION)
            min_version = TLS1_3_VERSION;
#endif
        /* Done massaging versions; do the check. */
        if (0
#ifdef OPENSSL_NO_SSL3
            || (min_version <= SSL3_VERSION && SSL3_VERSION <= max_version)
#endif
#ifdef OPENSSL_NO_TLS1
            || (min_version <= TLS1_VERSION && TLS1_VERSION <= max_version)
#endif
#ifdef OPENSSL_NO_TLS1_1
            || (min_version <= TLS1_1_VERSION && TLS1_1_VERSION <= max_version)
#endif
#ifdef OPENSSL_NO_TLS1_2
            || (min_version <= TLS1_2_VERSION && TLS1_2_VERSION <= max_version)
#endif
#ifdef OPENSSL_NO_TLS1_3
            || (min_version <= TLS1_3_VERSION && TLS1_3_VERSION <= max_version)
#endif
            )
            return 0;
    }
    return 1;
}