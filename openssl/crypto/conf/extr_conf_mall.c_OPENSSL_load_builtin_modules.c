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
 int /*<<< orphan*/  ASN1_add_oid_module () ; 
 int /*<<< orphan*/  ASN1_add_stable_module () ; 
 int /*<<< orphan*/  ENGINE_add_conf_module () ; 
 int /*<<< orphan*/  EVP_add_alg_module () ; 
 int /*<<< orphan*/  conf_add_ssl_module () ; 
 int /*<<< orphan*/  ossl_provider_add_conf_module () ; 

void OPENSSL_load_builtin_modules(void)
{
    /* Add builtin modules here */
    ASN1_add_oid_module();
    ASN1_add_stable_module();
#ifndef OPENSSL_NO_ENGINE
    ENGINE_add_conf_module();
#endif
    EVP_add_alg_module();
    conf_add_ssl_module();
    ossl_provider_add_conf_module();
}