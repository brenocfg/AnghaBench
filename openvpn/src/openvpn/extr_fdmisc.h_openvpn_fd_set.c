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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 

__attribute__((used)) static inline void
openvpn_fd_set(int fd, fd_set *setp)
{
#ifndef _WIN32 /* The Windows FD_SET() implementation does not overflow */
    ASSERT(fd >= 0 && fd < FD_SETSIZE);
#endif
    FD_SET(fd, setp);
}