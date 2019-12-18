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
 int /*<<< orphan*/  clean_onexit ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  lsapi_clean_shutdown () ; 

__attribute__((used)) static void lsapi_sigterm(int signal)
{

    // fprintf(stderr, "lsapi_sigterm: %d: clean_onexit %d\n", getpid(), clean_onexit );
    if(!clean_onexit)
    {
        lsapi_clean_shutdown();
    }
    exit(1);
}