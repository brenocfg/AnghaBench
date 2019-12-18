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
typedef  int /*<<< orphan*/  uint32 ;
struct SYSCACHECALLBACK {int id; int link; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int SysCacheSize ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int* syscache_callback_links ; 
 struct SYSCACHECALLBACK* syscache_callback_list ; 

void
CallSyscacheCallbacks(int cacheid, uint32 hashvalue)
{
	int			i;

	if (cacheid < 0 || cacheid >= SysCacheSize)
		elog(ERROR, "invalid cache ID: %d", cacheid);

	i = syscache_callback_links[cacheid] - 1;
	while (i >= 0)
	{
		struct SYSCACHECALLBACK *ccitem = syscache_callback_list + i;

		Assert(ccitem->id == cacheid);
		ccitem->function(ccitem->arg, cacheid, hashvalue);
		i = ccitem->link - 1;
	}
}