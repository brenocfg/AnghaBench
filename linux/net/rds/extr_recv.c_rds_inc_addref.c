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
struct rds_incoming {int /*<<< orphan*/  i_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdsdebug (char*,struct rds_incoming*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_inc_addref(struct rds_incoming *inc)
{
	rdsdebug("addref inc %p ref %d\n", inc, refcount_read(&inc->i_refcount));
	refcount_inc(&inc->i_refcount);
}