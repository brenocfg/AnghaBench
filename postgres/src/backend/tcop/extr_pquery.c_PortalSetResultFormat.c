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
typedef  scalar_t__ int16 ;
struct TYPE_5__ {scalar_t__* formats; int /*<<< orphan*/  portalContext; TYPE_1__* tupDesc; } ;
struct TYPE_4__ {int natts; } ;
typedef  TYPE_2__* Portal ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

void
PortalSetResultFormat(Portal portal, int nFormats, int16 *formats)
{
	int			natts;
	int			i;

	/* Do nothing if portal won't return tuples */
	if (portal->tupDesc == NULL)
		return;
	natts = portal->tupDesc->natts;
	portal->formats = (int16 *)
		MemoryContextAlloc(portal->portalContext,
						   natts * sizeof(int16));
	if (nFormats > 1)
	{
		/* format specified for each column */
		if (nFormats != natts)
			ereport(ERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("bind message has %d result formats but query has %d columns",
							nFormats, natts)));
		memcpy(portal->formats, formats, natts * sizeof(int16));
	}
	else if (nFormats > 0)
	{
		/* single format specified, use for all columns */
		int16		format1 = formats[0];

		for (i = 0; i < natts; i++)
			portal->formats[i] = format1;
	}
	else
	{
		/* use default format for all columns */
		for (i = 0; i < natts; i++)
			portal->formats[i] = 0;
	}
}