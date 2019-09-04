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
 int __hdaps_read_pair (unsigned int,unsigned int,int*,int*) ; 
 int /*<<< orphan*/  hdaps_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdaps_read_pair(unsigned int port1, unsigned int port2,
			   int *val1, int *val2)
{
	int ret;

	mutex_lock(&hdaps_mtx);
	ret = __hdaps_read_pair(port1, port2, val1, val2);
	mutex_unlock(&hdaps_mtx);

	return ret;
}