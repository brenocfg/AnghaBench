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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  TLS_GROUP_INFO ;

/* Variables and functions */
 int OSSL_NELEM (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* nid_list ; 

const TLS_GROUP_INFO *tls1_group_id_lookup(uint16_t group_id)
{
    /* ECC curves from RFC 4492 and RFC 7027 */
    if (group_id < 1 || group_id > OSSL_NELEM(nid_list))
        return NULL;
    return &nid_list[group_id - 1];
}