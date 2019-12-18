#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* ip; struct TYPE_4__* email; struct TYPE_4__* peername; int /*<<< orphan*/  hosts; int /*<<< orphan*/  policies; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_free ; 

void X509_VERIFY_PARAM_free(X509_VERIFY_PARAM *param)
{
    if (param == NULL)
        return;
    sk_ASN1_OBJECT_pop_free(param->policies, ASN1_OBJECT_free);
    sk_OPENSSL_STRING_pop_free(param->hosts, str_free);
    OPENSSL_free(param->peername);
    OPENSSL_free(param->email);
    OPENSSL_free(param->ip);
    OPENSSL_free(param);
}