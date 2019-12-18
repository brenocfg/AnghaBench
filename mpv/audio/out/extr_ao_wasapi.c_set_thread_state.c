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
struct wasapi_state {int /*<<< orphan*/  thread_state; } ;
struct ao {struct wasapi_state* priv; } ;
typedef  enum wasapi_thread_state { ____Placeholder_wasapi_thread_state } wasapi_thread_state ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thread_wakeup (struct ao*) ; 

__attribute__((used)) static void set_thread_state(struct ao *ao,
                             enum wasapi_thread_state thread_state)
{
    struct wasapi_state *state = ao->priv;
    atomic_store(&state->thread_state, thread_state);
    thread_wakeup(ao);
}