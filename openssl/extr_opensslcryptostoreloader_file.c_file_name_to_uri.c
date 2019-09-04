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
struct TYPE_5__ {char const* uri; } ;
struct TYPE_6__ {TYPE_1__ dir; } ;
struct TYPE_7__ {TYPE_2__ _; } ;
typedef  TYPE_3__ OSSL_STORE_LOADER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_strlcat (char*,char const*,long) ; 
 char* OPENSSL_zalloc (long) ; 
 int /*<<< orphan*/  OSSL_STORE_F_FILE_NAME_TO_URI ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ends_with_dirsep (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int file_name_to_uri(OSSL_STORE_LOADER_CTX *ctx, const char *name,
                            char **data)
{
    assert(name != NULL);
    assert(data != NULL);
    {
        const char *pathsep = ends_with_dirsep(ctx->_.dir.uri) ? "" : "/";
        long calculated_length = strlen(ctx->_.dir.uri) + strlen(pathsep)
            + strlen(name) + 1 /* \0 */;

        *data = OPENSSL_zalloc(calculated_length);
        if (*data == NULL) {
            OSSL_STOREerr(OSSL_STORE_F_FILE_NAME_TO_URI, ERR_R_MALLOC_FAILURE);
            return 0;
        }

        OPENSSL_strlcat(*data, ctx->_.dir.uri, calculated_length);
        OPENSSL_strlcat(*data, pathsep, calculated_length);
        OPENSSL_strlcat(*data, name, calculated_length);
    }
    return 1;
}