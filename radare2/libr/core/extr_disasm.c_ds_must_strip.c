#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__* strip; TYPE_1__ analop; } ;
typedef  TYPE_2__ RDisasmState ;

/* Variables and functions */
 char* r_anal_optype_to_string (int /*<<< orphan*/ ) ; 
 int strstr (scalar_t__*,char const*) ; 

__attribute__((used)) static bool ds_must_strip(RDisasmState *ds) {
	if (ds && ds->strip && *ds->strip) {
		const char * optype = r_anal_optype_to_string (ds->analop.type);
		if (optype && *optype) {
			return strstr (ds->strip, optype);
		}
	}
	return false;
}