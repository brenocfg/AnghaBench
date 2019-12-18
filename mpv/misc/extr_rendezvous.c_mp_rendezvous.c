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
struct waiter {void* tag; intptr_t* value; struct waiter* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct waiter* waiters ; 
 int /*<<< orphan*/  wakeup ; 

intptr_t mp_rendezvous(void *tag, intptr_t value)
{
    struct waiter wait = { .tag = tag, .value = &value };
    pthread_mutex_lock(&lock);
    struct waiter **prev = &waiters;
    while (*prev) {
        if ((*prev)->tag == tag) {
            intptr_t tmp = *(*prev)->value;
            *(*prev)->value = value;
            value = tmp;
            (*prev)->value = NULL; // signals completion
            *prev = (*prev)->next; // unlink
            pthread_cond_broadcast(&wakeup);
            goto done;
        }
        prev = &(*prev)->next;
    }
    *prev = &wait;
    while (wait.value)
        pthread_cond_wait(&wakeup, &lock);
done:
    pthread_mutex_unlock(&lock);
    return value;
}