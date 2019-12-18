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
struct tuntap {int /*<<< orphan*/ * fd; int /*<<< orphan*/  rw_handle; } ;
typedef  int /*<<< orphan*/ * event_t ;

/* Variables and functions */

__attribute__((used)) static inline event_t
tun_event_handle(const struct tuntap *tt)
{
#ifdef _WIN32
    return &tt->rw_handle;
#else
    return tt->fd;
#endif
}