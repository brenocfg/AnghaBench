#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* value; void* key; void* value_len; void* key_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {TYPE_2__ base; scalar_t__ expire; TYPE_1__ member_0; } ;
typedef  TYPE_3__ SdbKv ;
typedef  int /*<<< orphan*/  HtPPKv ;
typedef  int /*<<< orphan*/  HtPP ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int ht_pp_insert_kv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* strdup (void*) ; 
 void* strlen (void*) ; 

__attribute__((used)) static bool sdb_ht_internal_insert(HtPP* ht, const char* key,
				    const char* value, bool update) {
	if (!ht || !key || !value) {
		return false;
	}
	SdbKv kvp = {{ 0 }};
	kvp.base.key = strdup ((void *)key);
	if (!kvp.base.key) {
		goto err;
	}
	kvp.base.value = strdup ((void *)value);
	if (!kvp.base.value) {
		goto err;
	}
	kvp.base.key_len = strlen (kvp.base.key);
	kvp.base.value_len = strlen (kvp.base.value);
	kvp.expire = 0;
	return ht_pp_insert_kv (ht, (HtPPKv*)&kvp, update);

 err:
	free (kvp.base.key);
	free (kvp.base.value);
	return false;
}