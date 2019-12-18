#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int resultInitialized; int /*<<< orphan*/  passThrough; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {TYPE_2__* dest; TYPE_2__ const* src; } ;
struct TYPE_14__ {int numAttributes; int ntups; scalar_t__ nEvents; TYPE_5__* events; int /*<<< orphan*/  memorySize; int /*<<< orphan*/  noticeHooks; TYPE_1__** tuples; int /*<<< orphan*/  attDescs; int /*<<< orphan*/  cmdStatus; int /*<<< orphan*/  client_encoding; } ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ PGresult ;
typedef  TYPE_3__ PGEventResultCopy ;

/* Variables and functions */
 int /*<<< orphan*/  PGEVT_RESULTCOPY ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int PG_COPYRES_ATTRS ; 
 int PG_COPYRES_EVENTS ; 
 int PG_COPYRES_NOTICEHOOKS ; 
 int PG_COPYRES_TUPLES ; 
 int /*<<< orphan*/  PQclear (TYPE_2__*) ; 
 TYPE_2__* PQmakeEmptyPGresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQsetResultAttrs (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQsetvalue (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* dupEvents (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

PGresult *
PQcopyResult(const PGresult *src, int flags)
{
	PGresult   *dest;
	int			i;

	if (!src)
		return NULL;

	dest = PQmakeEmptyPGresult(NULL, PGRES_TUPLES_OK);
	if (!dest)
		return NULL;

	/* Always copy these over.  Is cmdStatus really useful here? */
	dest->client_encoding = src->client_encoding;
	strcpy(dest->cmdStatus, src->cmdStatus);

	/* Wants attrs? */
	if (flags & (PG_COPYRES_ATTRS | PG_COPYRES_TUPLES))
	{
		if (!PQsetResultAttrs(dest, src->numAttributes, src->attDescs))
		{
			PQclear(dest);
			return NULL;
		}
	}

	/* Wants to copy tuples? */
	if (flags & PG_COPYRES_TUPLES)
	{
		int			tup,
					field;

		for (tup = 0; tup < src->ntups; tup++)
		{
			for (field = 0; field < src->numAttributes; field++)
			{
				if (!PQsetvalue(dest, tup, field,
								src->tuples[tup][field].value,
								src->tuples[tup][field].len))
				{
					PQclear(dest);
					return NULL;
				}
			}
		}
	}

	/* Wants to copy notice hooks? */
	if (flags & PG_COPYRES_NOTICEHOOKS)
		dest->noticeHooks = src->noticeHooks;

	/* Wants to copy PGEvents? */
	if ((flags & PG_COPYRES_EVENTS) && src->nEvents > 0)
	{
		dest->events = dupEvents(src->events, src->nEvents,
								 &dest->memorySize);
		if (!dest->events)
		{
			PQclear(dest);
			return NULL;
		}
		dest->nEvents = src->nEvents;
	}

	/* Okay, trigger PGEVT_RESULTCOPY event */
	for (i = 0; i < dest->nEvents; i++)
	{
		if (src->events[i].resultInitialized)
		{
			PGEventResultCopy evt;

			evt.src = src;
			evt.dest = dest;
			if (!dest->events[i].proc(PGEVT_RESULTCOPY, &evt,
									  dest->events[i].passThrough))
			{
				PQclear(dest);
				return NULL;
			}
			dest->events[i].resultInitialized = true;
		}
	}

	return dest;
}