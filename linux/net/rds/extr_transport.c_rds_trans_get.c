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
struct rds_transport {int t_type; int /*<<< orphan*/  t_owner; } ;

/* Variables and functions */
 unsigned int RDS_TRANS_COUNT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_trans_sem ; 
 struct rds_transport** transports ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct rds_transport *rds_trans_get(int t_type)
{
	struct rds_transport *ret = NULL;
	struct rds_transport *trans;
	unsigned int i;

	down_read(&rds_trans_sem);
	for (i = 0; i < RDS_TRANS_COUNT; i++) {
		trans = transports[i];

		if (trans && trans->t_type == t_type &&
		    (!trans->t_owner || try_module_get(trans->t_owner))) {
			ret = trans;
			break;
		}
	}
	up_read(&rds_trans_sem);

	return ret;
}