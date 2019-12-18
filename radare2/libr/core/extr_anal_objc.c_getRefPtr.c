#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long long ut64 ;
struct TYPE_4__ {int /*<<< orphan*/  _const; int /*<<< orphan*/  _msgrefs; int /*<<< orphan*/  _selrefs; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RCoreObjc ;

/* Variables and functions */
 char* addr_key (long long) ; 
 scalar_t__ inBetween (int /*<<< orphan*/ ,long long) ; 
 long long readQword (TYPE_1__*,long long) ; 
 long long sdb_array_get_num (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 getRefPtr(RCoreObjc *objc, ut64 classMethodsVA, bool *res) {
	ut64 namePtr = readQword (objc, classMethodsVA);
	int i, cnt = 0;
	ut64 res_at = 0LL;
	const char *k = addr_key (namePtr);

	*res = false;
	for (i = 0; ; i++) {
		ut64 at = sdb_array_get_num (objc->db, k, i, NULL);
		if (!at) {
			break;
		}
		if (inBetween (objc->_selrefs, at)) {
			*res = false;
			res_at = at;
		} else if (inBetween (objc->_msgrefs, at)) {
			*res = true;
			res_at = at;
		} else if (inBetween (objc->_const, at)) {
			cnt++;
		}
	}
	if (cnt > 1) {
		return 0LL;
	}
	return res_at;
}