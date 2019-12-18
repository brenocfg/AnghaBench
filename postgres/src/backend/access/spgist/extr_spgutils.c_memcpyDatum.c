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
struct TYPE_3__ {unsigned int attlen; scalar_t__ attbyval; } ;
typedef  TYPE_1__ SpGistTypeDesc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetPointer (int /*<<< orphan*/ ) ; 
 unsigned int VARSIZE_ANY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
memcpyDatum(void *target, SpGistTypeDesc *att, Datum datum)
{
	unsigned int size;

	if (att->attbyval)
	{
		memcpy(target, &datum, sizeof(Datum));
	}
	else
	{
		size = (att->attlen > 0) ? att->attlen : VARSIZE_ANY(datum);
		memcpy(target, DatumGetPointer(datum), size);
	}
}