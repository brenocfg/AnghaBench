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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BEGINLEN ; 
 int BIO_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int LINESIZE ; 
 unsigned int PEM_FLAG_ONLY_B64 ; 
 int /*<<< orphan*/  PEM_F_GET_NAME ; 
 int /*<<< orphan*/  PEM_R_NO_START_LINE ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TAILLEN ; 
 int /*<<< orphan*/  beginstr ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pem_free (char*,unsigned int,int) ; 
 char* pem_malloc (int,unsigned int) ; 
 int sanitize_line (char*,int,unsigned int,int) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tailstr ; 

__attribute__((used)) static int get_name(BIO *bp, char **name, unsigned int flags)
{
    char *linebuf;
    int ret = 0;
    int len;
    int first_call = 1;

    /*
     * Need to hold trailing NUL (accounted for by BIO_gets() and the newline
     * that will be added by sanitize_line() (the extra '1').
     */
    linebuf = pem_malloc(LINESIZE + 1, flags);
    if (linebuf == NULL) {
        PEMerr(PEM_F_GET_NAME, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    do {
        len = BIO_gets(bp, linebuf, LINESIZE);

        if (len <= 0) {
            PEMerr(PEM_F_GET_NAME, PEM_R_NO_START_LINE);
            goto err;
        }

        /* Strip trailing garbage and standardize ending. */
        len = sanitize_line(linebuf, len, flags & ~PEM_FLAG_ONLY_B64, first_call);
        first_call = 0;

        /* Allow leading empty or non-matching lines. */
    } while (strncmp(linebuf, beginstr, BEGINLEN) != 0
             || len < TAILLEN
             || strncmp(linebuf + len - TAILLEN, tailstr, TAILLEN) != 0);
    linebuf[len - TAILLEN] = '\0';
    len = len - BEGINLEN - TAILLEN + 1;
    *name = pem_malloc(len, flags);
    if (*name == NULL) {
        PEMerr(PEM_F_GET_NAME, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    memcpy(*name, linebuf + BEGINLEN, len);
    ret = 1;

err:
    pem_free(linebuf, flags, LINESIZE + 1);
    return ret;
}