#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  peekbuf ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_9__ {int /*<<< orphan*/ * file; } ;
struct TYPE_8__ {scalar_t__ last_errno; int end_reached; int /*<<< orphan*/ * last_entry; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * uri; } ;
struct TYPE_10__ {TYPE_2__ file; TYPE_1__ dir; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; TYPE_3__ _; } ;
typedef  TYPE_4__ OSSL_STORE_LOADER_CTX ;
typedef  int /*<<< orphan*/  OSSL_STORE_LOADER ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_buffer_peek (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_f_buffer () ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_LIB_SYS ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/ * OPENSSL_DIR_read (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 TYPE_4__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  OSSL_STORE_F_FILE_OPEN ; 
 int /*<<< orphan*/  OSSL_STORE_LOADER_CTX_free (TYPE_4__*) ; 
 int /*<<< orphan*/  OSSL_STORE_R_PATH_MUST_BE_ABSOLUTE ; 
 int /*<<< orphan*/  OSSL_STORE_R_URI_AUTHORITY_UNSUPPORTED ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  is_dir ; 
 int /*<<< orphan*/  is_pem ; 
 scalar_t__ openssl_strerror_r (scalar_t__,char*,int) ; 
 char ossl_tolower (char const) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static OSSL_STORE_LOADER_CTX *file_open(const OSSL_STORE_LOADER *loader,
                                        const char *uri,
                                        const UI_METHOD *ui_method,
                                        void *ui_data)
{
    OSSL_STORE_LOADER_CTX *ctx = NULL;
    struct stat st;
    struct {
        const char *path;
        unsigned int check_absolute:1;
    } path_data[2];
    size_t path_data_n = 0, i;
    const char *path;

    /*
     * First step, just take the URI as is.
     */
    path_data[path_data_n].check_absolute = 0;
    path_data[path_data_n++].path = uri;

    /*
     * Second step, if the URI appears to start with the 'file' scheme,
     * extract the path and make that the second path to check.
     * There's a special case if the URI also contains an authority, then
     * the full URI shouldn't be used as a path anywhere.
     */
    if (strncasecmp(uri, "file:", 5) == 0) {
        const char *p = &uri[5];

        if (strncmp(&uri[5], "//", 2) == 0) {
            path_data_n--;           /* Invalidate using the full URI */
            if (strncasecmp(&uri[7], "localhost/", 10) == 0) {
                p = &uri[16];
            } else if (uri[7] == '/') {
                p = &uri[7];
            } else {
                OSSL_STOREerr(OSSL_STORE_F_FILE_OPEN,
                              OSSL_STORE_R_URI_AUTHORITY_UNSUPPORTED);
                return NULL;
            }
        }

        path_data[path_data_n].check_absolute = 1;
#ifdef _WIN32
        /* Windows file: URIs with a drive letter start with a / */
        if (p[0] == '/' && p[2] == ':' && p[3] == '/') {
            char c = ossl_tolower(p[1]);

            if (c >= 'a' && c <= 'z') {
                p++;
                /* We know it's absolute, so no need to check */
                path_data[path_data_n].check_absolute = 0;
            }
        }
#endif
        path_data[path_data_n++].path = p;
    }


    for (i = 0, path = NULL; path == NULL && i < path_data_n; i++) {
        /*
         * If the scheme "file" was an explicit part of the URI, the path must
         * be absolute.  So says RFC 8089
         */
        if (path_data[i].check_absolute && path_data[i].path[0] != '/') {
            OSSL_STOREerr(OSSL_STORE_F_FILE_OPEN,
                          OSSL_STORE_R_PATH_MUST_BE_ABSOLUTE);
            ERR_add_error_data(1, path_data[i].path);
            return NULL;
        }

        if (stat(path_data[i].path, &st) < 0) {
            ERR_raise_data(ERR_LIB_SYS, errno,
                           "calling stat(%s)",
                           path_data[i].path);
        } else {
            path = path_data[i].path;
        }
    }
    if (path == NULL) {
        return NULL;
    }

    /* Successfully found a working path, clear possible collected errors */
    ERR_clear_error();

    ctx = OPENSSL_zalloc(sizeof(*ctx));
    if (ctx == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_FILE_OPEN, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (S_ISDIR(st.st_mode)) {
        /*
         * Try to copy everything, even if we know that some of them must be
         * NULL for the moment.  This prevents errors in the future, when more
         * components may be used.
         */
        ctx->_.dir.uri = OPENSSL_strdup(uri);
        ctx->type = is_dir;

        if (ctx->_.dir.uri == NULL)
            goto err;

        ctx->_.dir.last_entry = OPENSSL_DIR_read(&ctx->_.dir.ctx, path);
        ctx->_.dir.last_errno = errno;
        if (ctx->_.dir.last_entry == NULL) {
            if (ctx->_.dir.last_errno != 0) {
                char errbuf[256];
                OSSL_STOREerr(OSSL_STORE_F_FILE_OPEN, ERR_R_SYS_LIB);
                errno = ctx->_.dir.last_errno;
                if (openssl_strerror_r(errno, errbuf, sizeof(errbuf)))
                    ERR_add_error_data(1, errbuf);
                goto err;
            }
            ctx->_.dir.end_reached = 1;
        }
    } else {
        BIO *buff = NULL;
        char peekbuf[4096] = { 0, };

        if ((buff = BIO_new(BIO_f_buffer())) == NULL
            || (ctx->_.file.file = BIO_new_file(path, "rb")) == NULL) {
            BIO_free_all(buff);
            goto err;
        }

        ctx->_.file.file = BIO_push(buff, ctx->_.file.file);
        if (BIO_buffer_peek(ctx->_.file.file, peekbuf, sizeof(peekbuf) - 1) > 0) {
            peekbuf[sizeof(peekbuf) - 1] = '\0';
            if (strstr(peekbuf, "-----BEGIN ") != NULL)
                ctx->type = is_pem;
        }
    }

    return ctx;
 err:
    OSSL_STORE_LOADER_CTX_free(ctx);
    return NULL;
}