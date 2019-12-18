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

/* Variables and functions */
 int const EAGAIN ; 
 int const ENOBUFS ; 
 int const WSAEINVAL ; 
 int const WSAEWOULDBLOCK ; 

__attribute__((used)) static inline bool
ignore_sys_error(const int err)
{
    /* I/O operation pending */
#ifdef _WIN32
    if (err == WSAEWOULDBLOCK || err == WSAEINVAL)
    {
        return true;
    }
#else
    if (err == EAGAIN)
    {
        return true;
    }
#endif

#if 0 /* if enabled, suppress ENOBUFS errors */
#ifdef ENOBUFS
    /* No buffer space available */
    if (err == ENOBUFS)
    {
        return true;
    }
#endif
#endif

    return false;
}