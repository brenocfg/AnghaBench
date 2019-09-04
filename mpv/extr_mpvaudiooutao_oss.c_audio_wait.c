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
struct priv {int /*<<< orphan*/  audio_fd; } ;
struct pollfd {int revents; int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int POLLERR ; 
 int POLLNVAL ; 
 int /*<<< orphan*/  POLLOUT ; 
 int ao_wait_poll (struct ao*,struct pollfd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_wait(struct ao *ao, pthread_mutex_t *lock)
{
    struct priv *p = ao->priv;

    struct pollfd fd = {.fd = p->audio_fd, .events = POLLOUT};
    int r = ao_wait_poll(ao, &fd, 1, lock);
    if (fd.revents & (POLLERR | POLLNVAL))
        return -1;
    return r;
}