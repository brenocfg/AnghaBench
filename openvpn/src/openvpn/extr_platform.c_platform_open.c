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
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int _wopen (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  wide_string (char const*,struct gc_arena*) ; 

int
platform_open(const char *path, int flags, int mode)
{
#ifdef _WIN32
    struct gc_arena gc = gc_new();
    int fd = _wopen(wide_string(path, &gc), flags, mode);
    gc_free(&gc);
    return fd;
#else
    return open(path, flags, mode);
#endif
}