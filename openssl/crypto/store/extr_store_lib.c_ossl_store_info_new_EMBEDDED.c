#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pem_name; int /*<<< orphan*/ * blob; } ;
struct TYPE_7__ {TYPE_2__ embedded; } ;
struct TYPE_9__ {TYPE_1__ _; } ;
typedef  TYPE_3__ OSSL_STORE_INFO ;
typedef  int /*<<< orphan*/  BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_INFO_NEW_EMBEDDED ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_EMBEDDED ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_free (TYPE_3__*) ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* store_info_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

OSSL_STORE_INFO *ossl_store_info_new_EMBEDDED(const char *new_pem_name,
                                              BUF_MEM *embedded)
{
    OSSL_STORE_INFO *info = store_info_new(OSSL_STORE_INFO_EMBEDDED, NULL);

    if (info == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INFO_NEW_EMBEDDED,
                      ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    info->_.embedded.blob = embedded;
    info->_.embedded.pem_name =
        new_pem_name == NULL ? NULL : OPENSSL_strdup(new_pem_name);

    if (new_pem_name != NULL && info->_.embedded.pem_name == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INFO_NEW_EMBEDDED,
                      ERR_R_MALLOC_FAILURE);
        OSSL_STORE_INFO_free(info);
        info = NULL;
    }

    return info;
}