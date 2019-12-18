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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,char,scalar_t__,int,int) ; 
 int /*<<< orphan*/  OSSL_NELEM (void**) ; 
 int backtrace (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backtrace_symbols_fd (void**,int,scalar_t__) ; 
 scalar_t__ md_count ; 
 int md_fail_percent ; 
 scalar_t__ md_tracefd ; 
 int /*<<< orphan*/  parseit () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int random () ; 
 int strlen (char*) ; 
 int write (scalar_t__,char*,int) ; 

__attribute__((used)) static int shouldfail(void)
{
    int roll = (int)(random() % 100);
    int shoulditfail = roll < md_fail_percent;
# ifndef _WIN32
/* suppressed on Windows as POSIX-like file descriptors are non-inheritable */
    int len;
    char buff[80];

    if (md_tracefd > 0) {
        BIO_snprintf(buff, sizeof(buff),
                     "%c C%ld %%%d R%d\n",
                     shoulditfail ? '-' : '+', md_count, md_fail_percent, roll);
        len = strlen(buff);
        if (write(md_tracefd, buff, len) != len)
            perror("shouldfail write failed");
#  ifndef OPENSSL_NO_CRYPTO_MDEBUG_BACKTRACE
        if (shoulditfail) {
            void *addrs[30];
            int num = backtrace(addrs, OSSL_NELEM(addrs));

            backtrace_symbols_fd(addrs, num, md_tracefd);
        }
#  endif
    }
# endif

    if (md_count) {
        /* If we used up this one, go to the next. */
        if (--md_count == 0)
            parseit();
    }

    return shoulditfail;
}