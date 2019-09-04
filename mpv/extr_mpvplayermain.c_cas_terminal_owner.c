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
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct MPContext* terminal_owner ; 
 int /*<<< orphan*/  terminal_owner_lock ; 

__attribute__((used)) static bool cas_terminal_owner(struct MPContext *old, struct MPContext *new)
{
    pthread_mutex_lock(&terminal_owner_lock);
    bool r = terminal_owner == old;
    if (r)
        terminal_owner = new;
    pthread_mutex_unlock(&terminal_owner_lock);
    return r;
}