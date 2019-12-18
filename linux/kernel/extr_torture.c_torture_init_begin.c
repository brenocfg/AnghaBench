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
 int /*<<< orphan*/  FULLSTOP_DONTSTOP ; 
 int /*<<< orphan*/  fullstop ; 
 int /*<<< orphan*/  fullstop_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_alert (char*,...) ; 
 char* torture_type ; 
 int verbose ; 

bool torture_init_begin(char *ttype, int v)
{
	mutex_lock(&fullstop_mutex);
	if (torture_type != NULL) {
		pr_alert("torture_init_begin: Refusing %s init: %s running.\n",
			 ttype, torture_type);
		pr_alert("torture_init_begin: One torture test at a time!\n");
		mutex_unlock(&fullstop_mutex);
		return false;
	}
	torture_type = ttype;
	verbose = v;
	fullstop = FULLSTOP_DONTSTOP;
	return true;
}