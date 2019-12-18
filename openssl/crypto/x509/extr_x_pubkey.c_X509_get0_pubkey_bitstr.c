#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* key; } ;
struct TYPE_7__ {TYPE_2__ cert_info; } ;
typedef  TYPE_3__ X509 ;
struct TYPE_5__ {int /*<<< orphan*/ * public_key; } ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */

ASN1_BIT_STRING *X509_get0_pubkey_bitstr(const X509 *x)
{
    if (x == NULL)
        return NULL;
    return x->cert_info.key->public_key;
}