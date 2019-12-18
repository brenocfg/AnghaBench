#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* core; } ;
struct TYPE_6__ {TYPE_1__* anal; } ;
struct TYPE_5__ {int /*<<< orphan*/  sdb_types; } ;
typedef  TYPE_3__ RCoreVisualTypes ;

/* Variables and functions */
 int /*<<< orphan*/  sdb_fmt (char*,char const*) ; 
 char* sdb_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *getformat (RCoreVisualTypes *vt, const char *k) {
	return sdb_get (vt->core->anal->sdb_types,
		sdb_fmt ("type.%s", k), 0);
}