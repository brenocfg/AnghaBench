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
struct fc4_prov {scalar_t__ recv; } ;
typedef  enum fc_fh_type { ____Placeholder_fc_fh_type } fc_fh_type ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FC_FC4_PROV_SIZE ; 
 struct fc4_prov** fc_active_prov ; 
 struct fc4_prov** fc_passive_prov ; 
 int /*<<< orphan*/  fc_prov_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int fc_fc4_register_provider(enum fc_fh_type type, struct fc4_prov *prov)
{
	struct fc4_prov **prov_entry;
	int ret = 0;

	if (type >= FC_FC4_PROV_SIZE)
		return -EINVAL;
	mutex_lock(&fc_prov_mutex);
	prov_entry = (prov->recv ? fc_passive_prov : fc_active_prov) + type;
	if (*prov_entry)
		ret = -EBUSY;
	else
		*prov_entry = prov;
	mutex_unlock(&fc_prov_mutex);
	return ret;
}