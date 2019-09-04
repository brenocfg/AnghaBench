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
struct ao_pull_state {int /*<<< orphan*/  state; } ;
struct ao {struct ao_pull_state* api_priv; } ;

/* Variables and functions */
 int AO_STATE_BUSY ; 
 scalar_t__ atomic_compare_exchange_strong (int /*<<< orphan*/ *,int*,int) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_sleep_us (int) ; 

__attribute__((used)) static void set_state(struct ao *ao, int new_state)
{
    struct ao_pull_state *p = ao->api_priv;
    while (1) {
        int old = atomic_load(&p->state);
        if (old == AO_STATE_BUSY) {
            // A spinlock, because some audio APIs don't want us to use mutexes.
            mp_sleep_us(1);
            continue;
        }
        if (atomic_compare_exchange_strong(&p->state, &old, new_state))
            break;
    }
}