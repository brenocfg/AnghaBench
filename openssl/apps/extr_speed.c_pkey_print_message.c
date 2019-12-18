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

/* Variables and functions */
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,long,...) ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ mr ; 

__attribute__((used)) static void pkey_print_message(const char *str, const char *str2, long num,
                               unsigned int bits, int tm)
{
#ifdef SIGALRM
    BIO_printf(bio_err,
               mr ? "+DTP:%d:%s:%s:%d\n"
               : "Doing %u bits %s %s's for %ds: ", bits, str, str2, tm);
    (void)BIO_flush(bio_err);
    alarm(tm);
#else
    BIO_printf(bio_err,
               mr ? "+DNP:%ld:%d:%s:%s\n"
               : "Doing %ld %u bits %s %s's: ", num, bits, str, str2);
    (void)BIO_flush(bio_err);
#endif
}