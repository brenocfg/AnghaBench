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
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int MP_NO_LATIN1_FALLBACK ; 
 int /*<<< orphan*/  bstr_sanitize_utf8_latin1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bstr mp_iconv_to_utf8(struct mp_log *log, bstr buf, const char *cp, int flags)
{
#if HAVE_ICONV
    if (!cp || !cp[0] || mp_charset_is_utf8(cp))
        return buf;

    if (strcasecmp(cp, "ASCII") == 0)
        return buf;

    if (strcasecmp(cp, "UTF-8-BROKEN") == 0)
        return bstr_sanitize_utf8_latin1(NULL, buf);

    // Force CP949 over EUC-KR since iconv distinguishes them and
    // EUC-KR causes error on CP949 encoded data
    if (strcasecmp(cp, "EUC-KR") == 0)
      cp = "CP949";

    iconv_t icdsc;
    if ((icdsc = iconv_open("UTF-8", cp)) == (iconv_t) (-1)) {
        if (flags & MP_ICONV_VERBOSE)
            mp_err(log, "Error opening iconv with codepage '%s'\n", cp);
        goto failure;
    }

    size_t size = buf.len;
    size_t osize = size;
    size_t ileft = size;
    size_t oleft = size - 1;

    char *outbuf = talloc_size(NULL, osize);
    char *ip = buf.start;
    char *op = outbuf;

    while (1) {
        int clear = 0;
        size_t rc;
        if (ileft)
            rc = iconv(icdsc, &ip, &ileft, &op, &oleft);
        else {
            clear = 1; // clear the conversion state and leave
            rc = iconv(icdsc, NULL, NULL, &op, &oleft);
        }
        if (rc == (size_t) (-1)) {
            if (errno == E2BIG) {
                size_t offset = op - outbuf;
                outbuf = talloc_realloc_size(NULL, outbuf, osize + size);
                op = outbuf + offset;
                osize += size;
                oleft += size;
            } else {
                if (errno == EINVAL && (flags & MP_ICONV_ALLOW_CUTOFF)) {
                    // This is intended for cases where the input buffer is cut
                    // at a random byte position. If this happens in the middle
                    // of the buffer, it should still be an error. We say it's
                    // fine if the error is within 10 bytes of the end.
                    if (ileft <= 10)
                        break;
                }
                if (flags & MP_ICONV_VERBOSE) {
                    mp_err(log, "Error recoding text with codepage '%s'\n", cp);
                }
                talloc_free(outbuf);
                iconv_close(icdsc);
                goto failure;
            }
        } else if (clear)
            break;
    }

    iconv_close(icdsc);

    outbuf[osize - oleft - 1] = 0;
    return (bstr){outbuf, osize - oleft - 1};
#endif

failure:
    if (flags & MP_NO_LATIN1_FALLBACK) {
        return buf;
    } else {
        return bstr_sanitize_utf8_latin1(NULL, buf);
    }
}