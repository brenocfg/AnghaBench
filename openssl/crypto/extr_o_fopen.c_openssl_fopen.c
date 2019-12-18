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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_FOPEN ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EBADF ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ERROR_INVALID_FLAGS ; 
 scalar_t__ ERROR_NO_UNICODE_TRANSLATION ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ MB_ERR_INVALID_CHARS ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,scalar_t__,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 int OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _PC_NAME_MAX ; 
 int /*<<< orphan*/ * _alloca (int) ; 
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int pathconf (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

FILE *openssl_fopen(const char *filename, const char *mode)
{
    FILE *file = NULL;
# if defined(_WIN32) && defined(CP_UTF8)
    int sz, len_0 = (int)strlen(filename) + 1;
    DWORD flags;

    /*
     * Basically there are three cases to cover: a) filename is
     * pure ASCII string; b) actual UTF-8 encoded string and
     * c) locale-ized string, i.e. one containing 8-bit
     * characters that are meaningful in current system locale.
     * If filename is pure ASCII or real UTF-8 encoded string,
     * MultiByteToWideChar succeeds and _wfopen works. If
     * filename is locale-ized string, chances are that
     * MultiByteToWideChar fails reporting
     * ERROR_NO_UNICODE_TRANSLATION, in which case we fall
     * back to fopen...
     */
    if ((sz = MultiByteToWideChar(CP_UTF8, (flags = MB_ERR_INVALID_CHARS),
                                  filename, len_0, NULL, 0)) > 0 ||
        (GetLastError() == ERROR_INVALID_FLAGS &&
         (sz = MultiByteToWideChar(CP_UTF8, (flags = 0),
                                   filename, len_0, NULL, 0)) > 0)
        ) {
        WCHAR wmode[8];
        WCHAR *wfilename = _alloca(sz * sizeof(WCHAR));

        if (MultiByteToWideChar(CP_UTF8, flags,
                                filename, len_0, wfilename, sz) &&
            MultiByteToWideChar(CP_UTF8, 0, mode, strlen(mode) + 1,
                                wmode, OSSL_NELEM(wmode)) &&
            (file = _wfopen(wfilename, wmode)) == NULL &&
            (errno == ENOENT || errno == EBADF)
            ) {
            /*
             * UTF-8 decode succeeded, but no file, filename
             * could still have been locale-ized...
             */
            file = fopen(filename, mode);
        }
    } else if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION) {
        file = fopen(filename, mode);
    }
# elif defined(__DJGPP__)
    {
        char *newname = NULL;

        if (pathconf(filename, _PC_NAME_MAX) <= 12) {  /* 8.3 file system? */
            char *iterator;
            char lastchar;

            if ((newname = OPENSSL_malloc(strlen(filename) + 1)) == NULL) {
                CRYPTOerr(CRYPTO_F_OPENSSL_FOPEN, ERR_R_MALLOC_FAILURE);
                return NULL;
            }

            for (iterator = newname, lastchar = '\0';
                *filename; filename++, iterator++) {
                if (lastchar == '/' && filename[0] == '.'
                    && filename[1] != '.' && filename[1] != '/') {
                    /* Leading dots are not permitted in plain DOS. */
                    *iterator = '_';
                } else {
                    *iterator = *filename;
                }
                lastchar = *filename;
            }
            *iterator = '\0';
            filename = newname;
        }
        file = fopen(filename, mode);

        OPENSSL_free(newname);
    }
# else
    file = fopen(filename, mode);
# endif
    return file;
}