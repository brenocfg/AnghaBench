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
 int /*<<< orphan*/  atoi (char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * md_failstring ; 
 int /*<<< orphan*/  md_tracefd ; 
 int /*<<< orphan*/  parseit () ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

void ossl_malloc_setup_failures(void)
{
    const char *cp = getenv("OPENSSL_MALLOC_FAILURES");

    if (cp != NULL && (md_failstring = strdup(cp)) != NULL)
        parseit();
    if ((cp = getenv("OPENSSL_MALLOC_FD")) != NULL)
        md_tracefd = atoi(cp);
}