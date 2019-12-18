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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CreateFileA (char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FILE_APPEND_DATA ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_TEMPORARY ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int _O_CREAT ; 
 int _O_RDONLY ; 
 int _O_TEMPORARY ; 
 int /*<<< orphan*/ * _fdopen (int,char*) ; 
 int _open_osfhandle (intptr_t,int) ; 
 int errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
pixie_fopen_shareable(FILE **in_fp, const char *filename, unsigned is_append)
{
    FILE *fp;

    *in_fp = NULL;

#if defined(WIN32)
    /* PORTABILITY: WINDOWS
     *  This bit of code deals with the fact that on Windows, fopen() opens
     *  a file so that it can't be moved. This code opens it a different
     *  way so that we can move it.
     *
     * NOTE: this is probably overkill, it appears that there is a better
     * API _fsopen() that does what I want without all this nonsense.
     */
    {
    HANDLE hFile;
    int fd;

    /* The normal POSIX C functions lock the file */
    /* int fd = open(filename, O_RDWR | O_CREAT, _S_IREAD | _S_IWRITE); */ /* Fails */
    /* int fd = _sopen(filename, O_RDWR | O_CREAT, _SH_DENYNO, _S_IREAD | _S_IWRITE); */ /* Also fails */

    /* We need to use WINAPI + _open_osfhandle to be able to use
       file descriptors (instead of WINAPI handles) */
    hFile = CreateFileA(    filename,
                            GENERIC_WRITE | (is_append?FILE_APPEND_DATA:0),
                            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                            NULL,
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_TEMPORARY,
                            NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return -1;
    }

    fd = _open_osfhandle((intptr_t)hFile, _O_CREAT | _O_RDONLY | _O_TEMPORARY);
    if (fd == -1) {
        perror("_open_osfhandle");
        return -1;
    }

    fp = _fdopen(fd, "w");
    }

#else
    fp = fopen(filename, is_append?"a":"w");
    if (fp == NULL)
        return errno;
#endif

    *in_fp = fp;
    return 0;
}