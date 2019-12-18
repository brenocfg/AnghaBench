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
typedef  size_t uint32 ;
typedef  scalar_t__ txid ;
struct TYPE_3__ {scalar_t__ xmin; scalar_t__ xmax; scalar_t__ nxip; scalar_t__* xip; } ;
typedef  TYPE_1__ TxidSnapshot ;

/* Variables and functions */
 scalar_t__ USE_BSEARCH_IF_NXIP_GREATER ; 
 void* bsearch (scalar_t__*,scalar_t__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_txid ; 

__attribute__((used)) static bool
is_visible_txid(txid value, const TxidSnapshot *snap)
{
	if (value < snap->xmin)
		return true;
	else if (value >= snap->xmax)
		return false;
#ifdef USE_BSEARCH_IF_NXIP_GREATER
	else if (snap->nxip > USE_BSEARCH_IF_NXIP_GREATER)
	{
		void	   *res;

		res = bsearch(&value, snap->xip, snap->nxip, sizeof(txid), cmp_txid);
		/* if found, transaction is still in progress */
		return (res) ? false : true;
	}
#endif
	else
	{
		uint32		i;

		for (i = 0; i < snap->nxip; i++)
		{
			if (value == snap->xip[i])
				return false;
		}
		return true;
	}
}