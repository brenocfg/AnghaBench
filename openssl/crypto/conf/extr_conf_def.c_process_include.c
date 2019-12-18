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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  OPENSSL_DIR_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  CONF_F_PROCESS_INCLUDE ; 
 int /*<<< orphan*/  CONF_R_RECURSIVE_DIRECTORY_INCLUDE ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_LIB_SYS ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*) ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * get_next_file (char*,int /*<<< orphan*/ **) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static BIO *process_include(char *include, OPENSSL_DIR_CTX **dirctx,
                            char **dirpath)
{
    struct stat st;
    BIO *next;

    if (stat(include, &st) < 0) {
        ERR_raise_data(ERR_LIB_SYS, errno,
                       "calling stat(%s)",
                       include);
        /* missing include file is not fatal error */
        return NULL;
    }

    if (S_ISDIR(st.st_mode)) {
        if (*dirctx != NULL) {
            CONFerr(CONF_F_PROCESS_INCLUDE,
                    CONF_R_RECURSIVE_DIRECTORY_INCLUDE);
            ERR_add_error_data(1, include);
            return NULL;
        }
        /* a directory, load its contents */
        if ((next = get_next_file(include, dirctx)) != NULL)
            *dirpath = include;
        return next;
    }

    next = BIO_new_file(include, "r");
    return next;
}