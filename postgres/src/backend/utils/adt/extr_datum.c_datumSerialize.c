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
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;
typedef  char Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetEOHP (char) ; 
 char* DatumGetPointer (char) ; 
 int /*<<< orphan*/  EOH_flatten_into (int /*<<< orphan*/ *,void*,int) ; 
 int EOH_get_flat_size (int /*<<< orphan*/ *) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (char*) ; 
 int datumGetSize (char,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,...) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 

void
datumSerialize(Datum value, bool isnull, bool typByVal, int typLen,
			   char **start_address)
{
	ExpandedObjectHeader *eoh = NULL;
	int			header;

	/* Write header word. */
	if (isnull)
		header = -2;
	else if (typByVal)
		header = -1;
	else if (typLen == -1 &&
			 VARATT_IS_EXTERNAL_EXPANDED(DatumGetPointer(value)))
	{
		eoh = DatumGetEOHP(value);
		header = EOH_get_flat_size(eoh);
	}
	else
		header = datumGetSize(value, typByVal, typLen);
	memcpy(*start_address, &header, sizeof(int));
	*start_address += sizeof(int);

	/* If not null, write payload bytes. */
	if (!isnull)
	{
		if (typByVal)
		{
			memcpy(*start_address, &value, sizeof(Datum));
			*start_address += sizeof(Datum);
		}
		else if (eoh)
		{
			char	   *tmp;

			/*
			 * EOH_flatten_into expects the target address to be maxaligned,
			 * so we can't store directly to *start_address.
			 */
			tmp = (char *) palloc(header);
			EOH_flatten_into(eoh, (void *) tmp, header);
			memcpy(*start_address, tmp, header);
			*start_address += header;

			/* be tidy. */
			pfree(tmp);
		}
		else
		{
			memcpy(*start_address, DatumGetPointer(value), header);
			*start_address += header;
		}
	}
}