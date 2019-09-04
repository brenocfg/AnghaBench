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
typedef  int /*<<< orphan*/  GLubyte ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,int /*<<< orphan*/  const*) ; 
 void* eglGetProcAddress (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void *get_proc_address(const GLubyte *name)
{
    void *p = eglGetProcAddress(name);
    // EGL 1.4 (supported by the RPI firmware) does not necessarily return
    // function pointers for core functions.
    if (!p) {
        void *h = dlopen("/opt/vc/lib/libGLESv2.so", RTLD_LAZY);
        if (h) {
            p = dlsym(h, name);
            dlclose(h);
        }
    }
    return p;
}