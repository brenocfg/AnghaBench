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
struct TYPE_5__ {int /*<<< orphan*/  search_name; } ;
struct TYPE_6__ {TYPE_1__ dir; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ _; } ;
typedef  int /*<<< orphan*/  OSSL_STORE_SEARCH ;
typedef  TYPE_3__ OSSL_STORE_LOADER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (int /*<<< orphan*/ ,int,char*,unsigned long) ; 
 int /*<<< orphan*/  OSSL_STORE_F_FILE_FIND ; 
 int /*<<< orphan*/  OSSL_STORE_R_SEARCH_ONLY_SUPPORTED_FOR_DIRECTORIES ; 
 int /*<<< orphan*/  OSSL_STORE_R_UNSUPPORTED_SEARCH_TYPE ; 
 scalar_t__ OSSL_STORE_SEARCH_BY_NAME ; 
 int /*<<< orphan*/  OSSL_STORE_SEARCH_get0_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ OSSL_STORE_SEARCH_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long X509_NAME_hash (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dir ; 

__attribute__((used)) static int file_find(OSSL_STORE_LOADER_CTX *ctx,
                     const OSSL_STORE_SEARCH *search)
{
    /*
     * If ctx == NULL, the library is looking to know if this loader supports
     * the given search type.
     */

    if (OSSL_STORE_SEARCH_get_type(search) == OSSL_STORE_SEARCH_BY_NAME) {
        unsigned long hash = 0;

        if (ctx == NULL)
            return 1;

        if (ctx->type != is_dir) {
            OSSL_STOREerr(OSSL_STORE_F_FILE_FIND,
                          OSSL_STORE_R_SEARCH_ONLY_SUPPORTED_FOR_DIRECTORIES);
            return 0;
        }

        hash = X509_NAME_hash(OSSL_STORE_SEARCH_get0_name(search));
        BIO_snprintf(ctx->_.dir.search_name, sizeof(ctx->_.dir.search_name),
                     "%08lx", hash);
        return 1;
    }

    if (ctx != NULL)
        OSSL_STOREerr(OSSL_STORE_F_FILE_FIND,
                      OSSL_STORE_R_UNSUPPORTED_SEARCH_TYPE);
    return 0;
}