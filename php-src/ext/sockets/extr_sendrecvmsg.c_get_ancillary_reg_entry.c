#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  ancillary_reg_entry ;
struct TYPE_3__ {int member_0; int member_1; } ;
typedef  TYPE_1__ anc_reg_key ;
struct TYPE_4__ {int /*<<< orphan*/  ht; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  ancillary_mutex ; 
 TYPE_2__ ancillary_registry ; 
 int /*<<< orphan*/  init_ancillary_registry () ; 
 int /*<<< orphan*/  tsrm_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsrm_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 

ancillary_reg_entry *get_ancillary_reg_entry(int cmsg_level, int msg_type)
{
	anc_reg_key			key = { cmsg_level, msg_type };
	ancillary_reg_entry	*entry;

#ifdef ZTS
	tsrm_mutex_lock(ancillary_mutex);
#endif
	if (!ancillary_registry.initialized) {
		init_ancillary_registry();
	}
#ifdef ZTS
	tsrm_mutex_unlock(ancillary_mutex);
#endif

	if ((entry = zend_hash_str_find_ptr(&ancillary_registry.ht, (char*)&key, sizeof(key))) != NULL) {
		return entry;
	} else {
		return NULL;
	}
}