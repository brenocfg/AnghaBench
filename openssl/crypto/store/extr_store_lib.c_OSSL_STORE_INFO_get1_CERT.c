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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int /*<<< orphan*/ * x509; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ _; } ;
typedef  TYPE_2__ OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_INFO_GET1_CERT ; 
 scalar_t__ OSSL_STORE_INFO_CERT ; 
 int /*<<< orphan*/  OSSL_STORE_R_NOT_A_CERTIFICATE ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 

X509 *OSSL_STORE_INFO_get1_CERT(const OSSL_STORE_INFO *info)
{
    if (info->type == OSSL_STORE_INFO_CERT) {
        X509_up_ref(info->_.x509);
        return info->_.x509;
    }
    OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INFO_GET1_CERT,
                  OSSL_STORE_R_NOT_A_CERTIFICATE);
    return NULL;
}