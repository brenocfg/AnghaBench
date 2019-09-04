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
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 int spawn_and_wait (char**) ; 

int main(int argc, char **argv)
{
    int naptime = 0;
    assert(argc > 2);

    naptime = atoi(argv[1]);
    assert(naptime > 0 && naptime < 1800);

    alarm(naptime);

    return spawn_and_wait(argv+2);
}