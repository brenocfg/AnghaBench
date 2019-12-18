#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* desc; TYPE_4__* name; } ;
struct TYPE_8__ {TYPE_4__* pem_name; int /*<<< orphan*/  blob; } ;
struct TYPE_9__ {int /*<<< orphan*/  crl; int /*<<< orphan*/  x509; int /*<<< orphan*/  pkey; int /*<<< orphan*/  params; TYPE_1__ name; TYPE_2__ embedded; } ;
struct TYPE_10__ {int type; TYPE_3__ _; } ;
typedef  TYPE_4__ OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_4__*) ; 
#define  OSSL_STORE_INFO_CERT 133 
#define  OSSL_STORE_INFO_CRL 132 
#define  OSSL_STORE_INFO_EMBEDDED 131 
#define  OSSL_STORE_INFO_NAME 130 
#define  OSSL_STORE_INFO_PARAMS 129 
#define  OSSL_STORE_INFO_PKEY 128 
 int /*<<< orphan*/  X509_CRL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 

void OSSL_STORE_INFO_free(OSSL_STORE_INFO *info)
{
    if (info != NULL) {
        switch (info->type) {
        case OSSL_STORE_INFO_EMBEDDED:
            BUF_MEM_free(info->_.embedded.blob);
            OPENSSL_free(info->_.embedded.pem_name);
            break;
        case OSSL_STORE_INFO_NAME:
            OPENSSL_free(info->_.name.name);
            OPENSSL_free(info->_.name.desc);
            break;
        case OSSL_STORE_INFO_PARAMS:
            EVP_PKEY_free(info->_.params);
            break;
        case OSSL_STORE_INFO_PKEY:
            EVP_PKEY_free(info->_.pkey);
            break;
        case OSSL_STORE_INFO_CERT:
            X509_free(info->_.x509);
            break;
        case OSSL_STORE_INFO_CRL:
            X509_CRL_free(info->_.crl);
            break;
        }
        OPENSSL_free(info);
    }
}