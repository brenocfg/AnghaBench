#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_10__ {TYPE_3__* new_cipher; } ;
struct TYPE_11__ {TYPE_1__ tmp; } ;
struct TYPE_13__ {int /*<<< orphan*/  server; TYPE_2__ s3; } ;
struct TYPE_12__ {unsigned long id; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_SECOP_CURVE_CHECK ; 
 unsigned long TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 ; 
 unsigned long TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 ; 
 scalar_t__ TLSEXT_curve_P_256 ; 
 scalar_t__ TLSEXT_curve_P_384 ; 
 int /*<<< orphan*/  tls1_get_peer_groups (TYPE_4__*,scalar_t__ const**,size_t*) ; 
 int /*<<< orphan*/  tls1_get_supported_groups (TYPE_4__*,scalar_t__ const**,size_t*) ; 
 int tls1_in_list (scalar_t__,scalar_t__ const*,size_t) ; 
 scalar_t__ tls1_suiteb (TYPE_4__*) ; 
 int /*<<< orphan*/  tls_group_allowed (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 

int tls1_check_group_id(SSL *s, uint16_t group_id, int check_own_groups)
    {
    const uint16_t *groups;
    size_t groups_len;

    if (group_id == 0)
        return 0;

    /* Check for Suite B compliance */
    if (tls1_suiteb(s) && s->s3.tmp.new_cipher != NULL) {
        unsigned long cid = s->s3.tmp.new_cipher->id;

        if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256) {
            if (group_id != TLSEXT_curve_P_256)
                return 0;
        } else if (cid == TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384) {
            if (group_id != TLSEXT_curve_P_384)
                return 0;
        } else {
            /* Should never happen */
            return 0;
        }
    }

    if (check_own_groups) {
        /* Check group is one of our preferences */
        tls1_get_supported_groups(s, &groups, &groups_len);
        if (!tls1_in_list(group_id, groups, groups_len))
            return 0;
    }

    if (!tls_group_allowed(s, group_id, SSL_SECOP_CURVE_CHECK))
        return 0;

    /* For clients, nothing more to check */
    if (!s->server)
        return 1;

    /* Check group is one of peers preferences */
    tls1_get_peer_groups(s, &groups, &groups_len);

    /*
     * RFC 4492 does not require the supported elliptic curves extension
     * so if it is not sent we can just choose any curve.
     * It is invalid to send an empty list in the supported groups
     * extension, so groups_len == 0 always means no extension.
     */
    if (groups_len == 0)
            return 1;
    return tls1_in_list(group_id, groups, groups_len);
}