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
struct tuntap {unsigned int rwflags_debug; } ;
struct event_set {int dummy; } ;

/* Variables and functions */
 unsigned int EVENT_READ ; 
 int /*<<< orphan*/  event_ctl (struct event_set*,int /*<<< orphan*/ ,unsigned int,void*) ; 
 int /*<<< orphan*/  tun_event_handle (struct tuntap*) ; 
 int /*<<< orphan*/  tun_read_queue (struct tuntap*,int /*<<< orphan*/ ) ; 
 scalar_t__ tuntap_defined (struct tuntap*) ; 

__attribute__((used)) static inline void
tun_set(struct tuntap *tt,
        struct event_set *es,
        unsigned int rwflags,
        void *arg,
        unsigned int *persistent)
{
    if (tuntap_defined(tt))
    {
        /* if persistent is defined, call event_ctl only if rwflags has changed since last call */
        if (!persistent || *persistent != rwflags)
        {
            event_ctl(es, tun_event_handle(tt), rwflags, arg);
            if (persistent)
            {
                *persistent = rwflags;
            }
        }
#ifdef _WIN32
        if (rwflags & EVENT_READ)
        {
            tun_read_queue(tt, 0);
        }
#endif
        tt->rwflags_debug = rwflags;
    }
}