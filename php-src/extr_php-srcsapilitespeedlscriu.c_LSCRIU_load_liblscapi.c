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
 void* DL_LOAD (char*) ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 char* dlerror () ; 
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 void* psem_close ; 
 void* psem_open ; 
 void* psem_post ; 
 void* s_lscapi_dump_me ; 
 void* s_lscapi_prepare_me ; 
 scalar_t__ s_native ; 
 int s_pid ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int LSCRIU_load_liblscapi(void)
{
    void *lib_handle = NULL;
    void *pthread_lib_handle = NULL;

    if (s_native)
        return 0;
    // Numerical signals indicates Apache
    int error = 1;
    char *last;

    if (!(lib_handle = DL_LOAD(last = "liblscapi.so")) /*||
        !(pthread_lib_handle = DL_LOAD(last = "libpthread.so"))*/)
        fprintf(stderr, "LSCRIU (%d): failed to dlopen %s: %s - ignore CRIU\n",
                s_pid, last, dlerror());
    else if (!(s_lscapi_dump_me = dlsym(lib_handle, last = "lscapi_dump_me")) ||
                !(s_lscapi_prepare_me = dlsym(lib_handle, last = "lscapi_prepare_me")) ||
                !(psem_open = dlsym(pthread_lib_handle, last = "sem_open")) ||
                !(psem_post = dlsym(pthread_lib_handle, last = "sem_post")) ||
                !(psem_close = dlsym(pthread_lib_handle, last = "sem_close")))
        fprintf(stderr, "LSCRIU (%d): failed to dlsym %s: %s - ignore CRIU\n",
                s_pid, last, dlerror());
    else
        error = 0;
    if (error) {
        // close the dll handles so we release the resources
        if (lib_handle)
            dlclose(lib_handle);
        if (pthread_lib_handle)
            dlclose(pthread_lib_handle);
        return -1;
    }
    return 0;
}