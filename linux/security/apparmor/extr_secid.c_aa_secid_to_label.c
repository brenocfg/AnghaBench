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
typedef  int /*<<< orphan*/  u32 ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_secids ; 
 struct aa_label* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct aa_label *aa_secid_to_label(u32 secid)
{
	struct aa_label *label;

	rcu_read_lock();
	label = idr_find(&aa_secids, secid);
	rcu_read_unlock();

	return label;
}