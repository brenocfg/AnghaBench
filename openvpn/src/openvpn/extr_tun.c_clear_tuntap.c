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
struct tuntap {int fd; int ip_fd; int /*<<< orphan*/ * hand; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct tuntap) ; 

__attribute__((used)) static void
clear_tuntap(struct tuntap *tuntap)
{
    CLEAR(*tuntap);
#ifdef _WIN32
    tuntap->hand = NULL;
#else
    tuntap->fd = -1;
#endif
#ifdef TARGET_SOLARIS
    tuntap->ip_fd = -1;
#endif
}