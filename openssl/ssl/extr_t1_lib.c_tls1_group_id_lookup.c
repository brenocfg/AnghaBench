#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ group_id; } ;
typedef  TYPE_1__ TLS_GROUP_INFO ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__ const*) ; 
 TYPE_1__ const* nid_list ; 

const TLS_GROUP_INFO *tls1_group_id_lookup(uint16_t group_id)
{
#if !defined(OPENSSL_NO_DH) || !defined(OPENSSL_NO_EC)
    size_t i;

    /* ECC curves from RFC 4492 and RFC 7027 FFDHE group from RFC 8446 */
    for (i = 0; i < OSSL_NELEM(nid_list); i++) {
        if (nid_list[i].group_id == group_id)
            return &nid_list[i];
    }
#endif /* !defined(OPENSSL_NO_DH) || !defined(OPENSSL_NO_EC) */
    return NULL;
}