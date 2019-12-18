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
 char* strerror_r (int,char*,size_t) ; 

__attribute__((used)) static inline char *strerror_thunk_r(int error_number, char *buffer, size_t len)
{
#ifdef __GLIBC__
    return strerror_r(error_number, buffer, len);
#else
    if (!strerror_r(error_number, buffer, len))
        return buffer;
    return "Unknown";
#endif
}