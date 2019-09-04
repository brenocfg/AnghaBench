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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (scalar_t__*) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int multi ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void killall(int ret, pid_t *kidpids)
{
    int i;

    for (i = 0; i < multi; ++i)
        if (kidpids[i] != 0)
            (void)kill(kidpids[i], SIGTERM);
    OPENSSL_free(kidpids);
    sleep(1);
    exit(ret);
}