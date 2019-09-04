#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_CRL ;
struct TYPE_4__ {int /*<<< orphan*/ * crl; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ _; } ;
typedef  TYPE_2__ OSSL_STORE_INFO ;

/* Variables and functions */
 scalar_t__ OSSL_STORE_INFO_CRL ; 

X509_CRL *OSSL_STORE_INFO_get0_CRL(const OSSL_STORE_INFO *info)
{
    if (info->type == OSSL_STORE_INFO_CRL)
        return info->_.crl;
    return NULL;
}