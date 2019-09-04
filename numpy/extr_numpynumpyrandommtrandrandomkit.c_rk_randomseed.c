#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int* key; scalar_t__ has_binomial; scalar_t__ has_gauss; scalar_t__ gauss; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ rk_state ;
typedef  scalar_t__ rk_error ;

/* Variables and functions */
 scalar_t__ RK_ENODEV ; 
 scalar_t__ RK_NOERR ; 
 int /*<<< orphan*/  RK_STATE_LEN ; 
 int /*<<< orphan*/  clock () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ rk_devfill (int*,int,int /*<<< orphan*/ ) ; 
 int rk_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_seed (int,TYPE_1__*) ; 

rk_error
rk_randomseed(rk_state *state)
{
#ifndef _WIN32
    struct timeval tv;
#else
    struct _timeb  tv;
#endif
    int i;

    if (rk_devfill(state->key, sizeof(state->key), 0) == RK_NOERR) {
        /* ensures non-zero key */
        state->key[0] |= 0x80000000UL;
        state->pos = RK_STATE_LEN;
        state->gauss = 0;
        state->has_gauss = 0;
        state->has_binomial = 0;

        for (i = 0; i < 624; i++) {
            state->key[i] &= 0xffffffffUL;
        }
        return RK_NOERR;
    }

#ifndef _WIN32
    gettimeofday(&tv, NULL);
    rk_seed(rk_hash(getpid()) ^ rk_hash(tv.tv_sec) ^ rk_hash(tv.tv_usec)
            ^ rk_hash(clock()), state);
#else
    _FTIME(&tv);
    rk_seed(rk_hash(tv.time) ^ rk_hash(tv.millitm) ^ rk_hash(clock()), state);
#endif

    return RK_ENODEV;
}