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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 unsigned long TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 ; 
 unsigned long TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 ; 
 int /*<<< orphan*/  TLSEXT_curve_P_256 ; 
 int /*<<< orphan*/  TLSEXT_curve_P_384 ; 
 int tls1_check_group_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tls1_shared_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls1_suiteb (int /*<<< orphan*/ *) ; 

int tls1_check_ec_tmp_key(SSL *s, unsigned long cid)
{
    /* If not Suite B just need a shared group */
    if (!tls1_suiteb(s))
        return tls1_shared_group(s, 0) != 0;
    /*
     * If Suite B, AES128 MUST use P-256 and AES256 MUST use P-384, no other
     * curves permitted.
     */
    if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256)
        return tls1_check_group_id(s, TLSEXT_curve_P_256, 1);
    if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384)
        return tls1_check_group_id(s, TLSEXT_curve_P_384, 1);

    return 0;
}