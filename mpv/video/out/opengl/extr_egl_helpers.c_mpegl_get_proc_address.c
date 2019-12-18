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
 int /*<<< orphan*/  RTLD_DEFAULT ; 
 void* dlsym (int /*<<< orphan*/ ,char const*) ; 
 void* eglGetProcAddress (char const*) ; 

__attribute__((used)) static void *mpegl_get_proc_address(void *ctx, const char *name)
{
    void *p = eglGetProcAddress(name);
#if defined(__GLIBC__) && HAVE_LIBDL
    // Some crappy ARM/Linux things do not provide EGL 1.5, so above call does
    // not necessarily return function pointers for core functions. Try to get
    // them from a loaded GLES lib. As POSIX leaves RTLD_DEFAULT "reserved",
    // use it only with glibc.
    if (!p)
        p = dlsym(RTLD_DEFAULT, name);
#endif
    return p;
}