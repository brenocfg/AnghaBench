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
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLOUT ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_writable(struct ao *ao)
{
    struct priv *p = ao->priv;
    struct pollfd fd = {.fd = p->audio_fd, .events = POLLOUT};
    return poll(&fd, 1, 0);
}