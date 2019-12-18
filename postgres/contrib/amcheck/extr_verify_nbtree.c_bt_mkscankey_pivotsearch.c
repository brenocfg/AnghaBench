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
struct TYPE_4__ {int pivotsearch; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__* BTScanInsert ;

/* Variables and functions */
 TYPE_1__* _bt_mkscankey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BTScanInsert
bt_mkscankey_pivotsearch(Relation rel, IndexTuple itup)
{
	BTScanInsert skey;

	skey = _bt_mkscankey(rel, itup);
	skey->pivotsearch = true;

	return skey;
}