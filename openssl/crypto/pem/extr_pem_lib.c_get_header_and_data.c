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
typedef  enum header_status { ____Placeholder_header_status } header_status ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_gets (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int ENDLEN ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int IN_HEADER ; 
 scalar_t__ LINESIZE ; 
 int MAYBE_HEADER ; 
 unsigned int PEM_FLAG_ONLY_B64 ; 
 int /*<<< orphan*/  PEM_F_GET_HEADER_AND_DATA ; 
 int /*<<< orphan*/  PEM_R_BAD_END_LINE ; 
 int /*<<< orphan*/  PEM_R_SHORT_HEADER ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int POST_HEADER ; 
 size_t TAILLEN ; 
 char* endstr ; 
 int /*<<< orphan*/ * memchr (char*,char,int) ; 
 int /*<<< orphan*/  pem_free (char*,unsigned int,scalar_t__) ; 
 char* pem_malloc (scalar_t__,unsigned int) ; 
 int sanitize_line (char*,int,unsigned int,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 char* tailstr ; 

__attribute__((used)) static int get_header_and_data(BIO *bp, BIO **header, BIO **data, char *name,
                               unsigned int flags)
{
    BIO *tmp = *header;
    char *linebuf, *p;
    int len, line, ret = 0, end = 0;
    /* 0 if not seen (yet), 1 if reading header, 2 if finished header */
    enum header_status got_header = MAYBE_HEADER;
    unsigned int flags_mask;
    size_t namelen;

    /* Need to hold trailing NUL (accounted for by BIO_gets() and the newline
     * that will be added by sanitize_line() (the extra '1'). */
    linebuf = pem_malloc(LINESIZE + 1, flags);
    if (linebuf == NULL) {
        PEMerr(PEM_F_GET_HEADER_AND_DATA, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    for (line = 0; ; line++) {
        flags_mask = ~0u;
        len = BIO_gets(bp, linebuf, LINESIZE);
        if (len <= 0) {
            PEMerr(PEM_F_GET_HEADER_AND_DATA, PEM_R_SHORT_HEADER);
            goto err;
        }

        if (got_header == MAYBE_HEADER) {
            if (memchr(linebuf, ':', len) != NULL)
                got_header = IN_HEADER;
        }
        if (!strncmp(linebuf, endstr, ENDLEN) || got_header == IN_HEADER)
            flags_mask &= ~PEM_FLAG_ONLY_B64;
        len = sanitize_line(linebuf, len, flags & flags_mask, 0);

        /* Check for end of header. */
        if (linebuf[0] == '\n') {
            if (got_header == POST_HEADER) {
                /* Another blank line is an error. */
                PEMerr(PEM_F_GET_HEADER_AND_DATA, PEM_R_BAD_END_LINE);
                goto err;
            }
            got_header = POST_HEADER;
            tmp = *data;
            continue;
        }

        /* Check for end of stream (which means there is no header). */
        if (strncmp(linebuf, endstr, ENDLEN) == 0) {
            p = linebuf + ENDLEN;
            namelen = strlen(name);
            if (strncmp(p, name, namelen) != 0 ||
                strncmp(p + namelen, tailstr, TAILLEN) != 0) {
                PEMerr(PEM_F_GET_HEADER_AND_DATA, PEM_R_BAD_END_LINE);
                goto err;
            }
            if (got_header == MAYBE_HEADER) {
                *header = *data;
                *data = tmp;
            }
            break;
        } else if (end) {
            /* Malformed input; short line not at end of data. */
            PEMerr(PEM_F_GET_HEADER_AND_DATA, PEM_R_BAD_END_LINE);
            goto err;
        }
        /*
         * Else, a line of text -- could be header or data; we don't
         * know yet.  Just pass it through.
         */
        if (BIO_puts(tmp, linebuf) < 0)
            goto err;
        /*
         * Only encrypted files need the line length check applied.
         */
        if (got_header == POST_HEADER) {
            /* 65 includes the trailing newline */
            if (len > 65)
                goto err;
            if (len < 65)
                end = 1;
        }
    }

    ret = 1;
err:
    pem_free(linebuf, flags, LINESIZE + 1);
    return ret;
}