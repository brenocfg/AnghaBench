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
typedef  int thread_key_t ;
typedef  int /*<<< orphan*/  mutex_t ;

/* Variables and functions */
 int TLS_OUT_OF_INDEXES ; 
 int TlsAlloc () ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ thr_getspecific (int) ; 
 scalar_t__ thr_setspecific (int,void*) ; 

__attribute__((used)) static int *
__nc_error()
{
	extern mutex_t nc_lock;
	extern thread_key_t nc_key;
	static int nc_error = 0;
	int error, *nc_addr;

	/*
	 * Use the static `nc_error' if we are the main thread
	 * (including non-threaded programs), or if an allocation
	 * fails.
	 */
	if (nc_key == -1) {
		error = 0;
		mutex_lock(&nc_lock);
		if (nc_key == -1)
			error = nc_key = TlsAlloc();	//thr_keycreate(&nc_key, free);
		mutex_unlock(&nc_lock);
		if (error == TLS_OUT_OF_INDEXES)
			return (&nc_error);
	}
	if ((nc_addr = (int *)thr_getspecific(nc_key)) == NULL) {
		nc_addr = (int *)malloc(sizeof (int *));
		if (thr_setspecific(nc_key, (void *) nc_addr) == 0) {
			if (nc_addr)
				free(nc_addr);
			return (&nc_error);
		}
		*nc_addr = 0;
	}
	return (nc_addr);
}