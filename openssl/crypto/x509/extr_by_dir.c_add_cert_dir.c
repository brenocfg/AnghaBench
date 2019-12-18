#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * dirs; } ;
struct TYPE_8__ {int dir_type; int /*<<< orphan*/ * hashes; int /*<<< orphan*/ * dir; } ;
typedef  TYPE_1__ BY_DIR_ENTRY ;
typedef  TYPE_2__ BY_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 char const LIST_SEPARATOR_CHAR ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * OPENSSL_strndup (char const*,size_t) ; 
 int /*<<< orphan*/  X509_F_ADD_CERT_DIR ; 
 int /*<<< orphan*/  X509_R_INVALID_DIRECTORY ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  by_dir_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  by_dir_hash_cmp ; 
 int /*<<< orphan*/ * sk_BY_DIR_ENTRY_new_null () ; 
 int sk_BY_DIR_ENTRY_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_BY_DIR_ENTRY_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* sk_BY_DIR_ENTRY_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sk_BY_DIR_HASH_new (int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int add_cert_dir(BY_DIR *ctx, const char *dir, int type)
{
    int j;
    size_t len;
    const char *s, *ss, *p;

    if (dir == NULL || *dir == '\0') {
        X509err(X509_F_ADD_CERT_DIR, X509_R_INVALID_DIRECTORY);
        return 0;
    }

    s = dir;
    p = s;
    do {
        if ((*p == LIST_SEPARATOR_CHAR) || (*p == '\0')) {
            BY_DIR_ENTRY *ent;

            ss = s;
            s = p + 1;
            len = p - ss;
            if (len == 0)
                continue;
            for (j = 0; j < sk_BY_DIR_ENTRY_num(ctx->dirs); j++) {
                ent = sk_BY_DIR_ENTRY_value(ctx->dirs, j);
                if (strlen(ent->dir) == len && strncmp(ent->dir, ss, len) == 0)
                    break;
            }
            if (j < sk_BY_DIR_ENTRY_num(ctx->dirs))
                continue;
            if (ctx->dirs == NULL) {
                ctx->dirs = sk_BY_DIR_ENTRY_new_null();
                if (!ctx->dirs) {
                    X509err(X509_F_ADD_CERT_DIR, ERR_R_MALLOC_FAILURE);
                    return 0;
                }
            }
            ent = OPENSSL_malloc(sizeof(*ent));
            if (ent == NULL) {
                X509err(X509_F_ADD_CERT_DIR, ERR_R_MALLOC_FAILURE);
                return 0;
            }
            ent->dir_type = type;
            ent->hashes = sk_BY_DIR_HASH_new(by_dir_hash_cmp);
            ent->dir = OPENSSL_strndup(ss, len);
            if (ent->dir == NULL || ent->hashes == NULL) {
                by_dir_entry_free(ent);
                return 0;
            }
            if (!sk_BY_DIR_ENTRY_push(ctx->dirs, ent)) {
                by_dir_entry_free(ent);
                X509err(X509_F_ADD_CERT_DIR, ERR_R_MALLOC_FAILURE);
                return 0;
            }
        }
    } while (*p++ != '\0');
    return 1;
}