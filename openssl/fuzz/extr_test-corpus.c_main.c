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

/* Variables and functions */
 int /*<<< orphan*/  FuzzerCleanup () ; 
 int /*<<< orphan*/  FuzzerInitialize (int*,char***) ; 
 int /*<<< orphan*/  OPENSSL_DIR_end (int /*<<< orphan*/ **) ; 
 char* OPENSSL_DIR_read (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  testfile (char*) ; 

int main(int argc, char **argv) {
    int n;

    FuzzerInitialize(&argc, &argv);

    for (n = 1; n < argc; ++n) {
        size_t dirname_len = strlen(argv[n]);
        const char *filename = NULL;
        char *pathname = NULL;
        OPENSSL_DIR_CTX *ctx = NULL;
        int wasdir = 0;

        /*
         * We start with trying to read the given path as a directory.
         */
        while ((filename = OPENSSL_DIR_read(&ctx, argv[n])) != NULL) {
            wasdir = 1;
            if (pathname == NULL) {
                pathname = malloc(PATH_MAX);
                if (pathname == NULL)
                    break;
                strcpy(pathname, argv[n]);
#ifdef __VMS
                if (strchr(":<]", pathname[dirname_len - 1]) == NULL)
#endif
                    pathname[dirname_len++] = '/';
                pathname[dirname_len] = '\0';
            }
            strcpy(pathname + dirname_len, filename);
            testfile(pathname);
        }
        OPENSSL_DIR_end(&ctx);

        /* If it wasn't a directory, treat it as a file instead */
        if (!wasdir)
            testfile(argv[n]);

        free(pathname);
    }

    FuzzerCleanup();

    return 0;
}