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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ GetCurrentProcessId () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nn_clock_ms () ; 
 int /*<<< orphan*/  nn_random_state ; 

void nn_random_seed ()
{
    uint64_t pid;

#ifdef NN_HAVE_WINDOWS
    pid = (uint64_t) GetCurrentProcessId ();
#else
    pid = (uint64_t) getpid ();
#endif

    /*  The initial state for pseudo-random number generator is computed from
        the exact timestamp and process ID. */
    memcpy (&nn_random_state, "\xfa\x9b\x23\xe3\x07\xcc\x61\x1f", 8);
    nn_random_state ^= pid + nn_clock_ms();
}