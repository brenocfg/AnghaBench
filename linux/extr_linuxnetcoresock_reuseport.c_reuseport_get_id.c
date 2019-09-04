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
struct sock_reuseport {int reuseport_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  REUSEPORT_MIN_ID ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reuseport_ida ; 

int reuseport_get_id(struct sock_reuseport *reuse)
{
	int id;

	if (reuse->reuseport_id)
		return reuse->reuseport_id;

	id = ida_simple_get(&reuseport_ida, REUSEPORT_MIN_ID, 0,
			    /* Called under reuseport_lock */
			    GFP_ATOMIC);
	if (id < 0)
		return id;

	reuse->reuseport_id = id;

	return reuse->reuseport_id;
}