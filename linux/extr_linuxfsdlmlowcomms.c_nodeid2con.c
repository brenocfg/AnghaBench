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
struct connection {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct connection* __nodeid2con (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connections_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct connection *nodeid2con(int nodeid, gfp_t allocation)
{
	struct connection *con;

	mutex_lock(&connections_lock);
	con = __nodeid2con(nodeid, allocation);
	mutex_unlock(&connections_lock);

	return con;
}