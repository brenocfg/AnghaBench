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
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/ * PKCS12_get_attr_gen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PKCS8_pkey_get0_attrs (int /*<<< orphan*/ *) ; 

ASN1_TYPE *PKCS8_get_attr(PKCS8_PRIV_KEY_INFO *p8, int attr_nid)
{
    return PKCS12_get_attr_gen(PKCS8_pkey_get0_attrs(p8), attr_nid);
}