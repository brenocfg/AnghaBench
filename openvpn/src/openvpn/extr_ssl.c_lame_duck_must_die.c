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
typedef  scalar_t__ time_t ;
struct tls_session {struct key_state* key; } ;
struct key_state {scalar_t__ state; scalar_t__ const must_die; } ;
typedef  int /*<<< orphan*/  interval_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__ const) ; 
 size_t KS_LAME_DUCK ; 
 scalar_t__ S_ERROR ; 
 scalar_t__ S_INITIAL ; 
 int /*<<< orphan*/  compute_earliest_wakeup (int /*<<< orphan*/ *,scalar_t__ const) ; 
 scalar_t__ now ; 

__attribute__((used)) static inline bool
lame_duck_must_die(const struct tls_session *session, interval_t *wakeup)
{
    const struct key_state *lame = &session->key[KS_LAME_DUCK];
    if (lame->state >= S_INITIAL)
    {
        const time_t local_now = now;
        ASSERT(lame->must_die); /* a lame duck key must always have an expiration */
        if (local_now < lame->must_die)
        {
            compute_earliest_wakeup(wakeup, lame->must_die - local_now);
            return false;
        }
        else
        {
            return true;
        }
    }
    else if (lame->state == S_ERROR)
    {
        return true;
    }
    else
    {
        return false;
    }
}