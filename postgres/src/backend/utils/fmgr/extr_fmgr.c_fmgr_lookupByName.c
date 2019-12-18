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
struct TYPE_4__ {int /*<<< orphan*/  funcName; } ;
typedef  TYPE_1__ FmgrBuiltin ;

/* Variables and functions */
 TYPE_1__ const* fmgr_builtins ; 
 int fmgr_nbuiltins ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const FmgrBuiltin *
fmgr_lookupByName(const char *name)
{
	int			i;

	for (i = 0; i < fmgr_nbuiltins; i++)
	{
		if (strcmp(name, fmgr_builtins[i].funcName) == 0)
			return fmgr_builtins + i;
	}
	return NULL;
}