#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bind; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RBinSymbol ;

/* Variables and functions */
 int /*<<< orphan*/  R_BIN_BIND_GLOBAL_STR ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool isAnExport(RBinSymbol *s) {
	/* workaround for some bin plugs */
	if (!strncmp (s->name, "imp.", 4)) {
		return false;
	}
	return (s->bind && !strcmp (s->bind, R_BIN_BIND_GLOBAL_STR));
}