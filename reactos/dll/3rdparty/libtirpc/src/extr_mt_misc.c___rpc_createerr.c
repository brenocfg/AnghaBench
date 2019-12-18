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
struct rpc_createerr {int dummy; } ;

/* Variables and functions */
 int TlsAlloc () ; 
 int /*<<< orphan*/  free (struct rpc_createerr*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct rpc_createerr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rce_key ; 
 struct rpc_createerr rpc_createerr ; 
 scalar_t__ thr_getspecific (int) ; 
 scalar_t__ thr_setspecific (int,void*) ; 
 int /*<<< orphan*/  tsd_lock ; 

struct rpc_createerr *
__rpc_createerr()
{
	struct rpc_createerr *rce_addr;

	mutex_lock(&tsd_lock);
	if (rce_key == -1)
		rce_key = TlsAlloc();	//thr_keycreate(&rce_key, free);
	mutex_unlock(&tsd_lock);

	rce_addr = (struct rpc_createerr *)thr_getspecific(rce_key);
	if (!rce_addr) {
		rce_addr = (struct rpc_createerr *)
			malloc(sizeof (struct rpc_createerr));
		if (!rce_addr ||
		    thr_setspecific(rce_key, (void *) rce_addr) == 0) {
			if (rce_addr)
				free(rce_addr);
			return (&rpc_createerr);
		}
		memset(rce_addr, 0, sizeof (struct rpc_createerr));
	}
	return (rce_addr);
}