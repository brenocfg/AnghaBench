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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*,long,int) ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ mr ; 

__attribute__((used)) static void print_message(const char *s, long num, int length, int tm)
{
#ifdef SIGALRM
    BIO_printf(bio_err,
               mr ? "+DT:%s:%d:%d\n"
               : "Doing %s for %ds on %d size blocks: ", s, tm, length);
    (void)BIO_flush(bio_err);
    alarm(tm);
#else
    BIO_printf(bio_err,
               mr ? "+DN:%s:%ld:%d\n"
               : "Doing %s %ld times on %d size blocks: ", s, num, length);
    (void)BIO_flush(bio_err);
#endif
}