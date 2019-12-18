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
typedef  int /*<<< orphan*/  OPENSSL_DIR_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  CONF_F_GET_NEXT_FILE ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_DIR_end (int /*<<< orphan*/ **) ; 
 char* OPENSSL_DIR_read (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  OPENSSL_strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char const*,size_t) ; 
 char* OPENSSL_zalloc (size_t) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static BIO *get_next_file(const char *path, OPENSSL_DIR_CTX **dirctx)
{
    const char *filename;
    size_t pathlen;

    pathlen = strlen(path);
    while ((filename = OPENSSL_DIR_read(dirctx, path)) != NULL) {
        size_t namelen;

        namelen = strlen(filename);


        if ((namelen > 5 && strcasecmp(filename + namelen - 5, ".conf") == 0)
            || (namelen > 4 && strcasecmp(filename + namelen - 4, ".cnf") == 0)) {
            size_t newlen;
            char *newpath;
            BIO *bio;

            newlen = pathlen + namelen + 2;
            newpath = OPENSSL_zalloc(newlen);
            if (newpath == NULL) {
                CONFerr(CONF_F_GET_NEXT_FILE, ERR_R_MALLOC_FAILURE);
                break;
            }
#ifdef OPENSSL_SYS_VMS
            /*
             * If the given path isn't clear VMS syntax,
             * we treat it as on Unix.
             */
            if (path[pathlen - 1] == ']'
                || path[pathlen - 1] == '>'
                || path[pathlen - 1] == ':') {
                /* Clear VMS directory syntax, just copy as is */
                OPENSSL_strlcpy(newpath, path, newlen);
            }
#endif
            if (newpath[0] == '\0') {
                OPENSSL_strlcpy(newpath, path, newlen);
                OPENSSL_strlcat(newpath, "/", newlen);
            }
            OPENSSL_strlcat(newpath, filename, newlen);

            bio = BIO_new_file(newpath, "r");
            OPENSSL_free(newpath);
            /* Errors when opening files are non-fatal. */
            if (bio != NULL)
                return bio;
        }
    }
    OPENSSL_DIR_end(dirctx);
    *dirctx = NULL;
    return NULL;
}