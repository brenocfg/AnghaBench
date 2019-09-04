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
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_DNS ; 
 int do_x509_check (int /*<<< orphan*/ *,char const*,size_t,unsigned int,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ memchr (char const*,char,size_t) ; 
 size_t strlen (char const*) ; 

int X509_check_host(X509 *x, const char *chk, size_t chklen,
                    unsigned int flags, char **peername)
{
    if (chk == NULL)
        return -2;
    /*
     * Embedded NULs are disallowed, except as the last character of a
     * string of length 2 or more (tolerate caller including terminating
     * NUL in string length).
     */
    if (chklen == 0)
        chklen = strlen(chk);
    else if (memchr(chk, '\0', chklen > 1 ? chklen - 1 : chklen))
        return -2;
    if (chklen > 1 && chk[chklen - 1] == '\0')
        --chklen;
    return do_x509_check(x, chk, chklen, flags, GEN_DNS, peername);
}