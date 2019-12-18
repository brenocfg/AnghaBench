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
struct clnt_ops {int /*<<< orphan*/  cl_control; int /*<<< orphan*/  cl_destroy; int /*<<< orphan*/  cl_freeres; int /*<<< orphan*/  cl_geterr; int /*<<< orphan*/  cl_abort; int /*<<< orphan*/ * cl_call; } ;
typedef  int /*<<< orphan*/  mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  clnt_raw_abort ; 
 int /*<<< orphan*/ * clnt_raw_call ; 
 int /*<<< orphan*/  clnt_raw_control ; 
 int /*<<< orphan*/  clnt_raw_destroy ; 
 int /*<<< orphan*/  clnt_raw_freeres ; 
 int /*<<< orphan*/  clnt_raw_geterr ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct clnt_ops *
clnt_raw_ops()
{
	static struct clnt_ops ops;
	extern mutex_t  ops_lock;

	/* VARIABLES PROTECTED BY ops_lock: ops */

	mutex_lock(&ops_lock);
	if (ops.cl_call == NULL) {
		ops.cl_call = clnt_raw_call;
		ops.cl_abort = clnt_raw_abort;
		ops.cl_geterr = clnt_raw_geterr;
		ops.cl_freeres = clnt_raw_freeres;
		ops.cl_destroy = clnt_raw_destroy;
		ops.cl_control = clnt_raw_control;
	}
	mutex_unlock(&ops_lock);
	return (&ops);
}