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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_5__ {int magic; int type; int nitems; TYPE_1__* items; } ;
struct TYPE_4__ {int ndistinct; int /*<<< orphan*/  attrs; } ;
typedef  int Size ;
typedef  TYPE_1__ MVNDistinctItem ;
typedef  TYPE_2__ MVNDistinct ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 int STATS_NDISTINCT_MAGIC ; 
 int STATS_NDISTINCT_TYPE_BASIC ; 
 int SizeOfHeader ; 
 int SizeOfItem (int) ; 
 char* VARDATA (int /*<<< orphan*/ *) ; 
 int VARHDRSZ ; 
 int bms_next_member (int /*<<< orphan*/ ,int) ; 
 int bms_num_members (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 scalar_t__ palloc (int) ; 

bytea *
statext_ndistinct_serialize(MVNDistinct *ndistinct)
{
	int			i;
	bytea	   *output;
	char	   *tmp;
	Size		len;

	Assert(ndistinct->magic == STATS_NDISTINCT_MAGIC);
	Assert(ndistinct->type == STATS_NDISTINCT_TYPE_BASIC);

	/*
	 * Base size is size of scalar fields in the struct, plus one base struct
	 * for each item, including number of items for each.
	 */
	len = VARHDRSZ + SizeOfHeader;

	/* and also include space for the actual attribute numbers */
	for (i = 0; i < ndistinct->nitems; i++)
	{
		int			nmembers;

		nmembers = bms_num_members(ndistinct->items[i].attrs);
		Assert(nmembers >= 2);

		len += SizeOfItem(nmembers);
	}

	output = (bytea *) palloc(len);
	SET_VARSIZE(output, len);

	tmp = VARDATA(output);

	/* Store the base struct values (magic, type, nitems) */
	memcpy(tmp, &ndistinct->magic, sizeof(uint32));
	tmp += sizeof(uint32);
	memcpy(tmp, &ndistinct->type, sizeof(uint32));
	tmp += sizeof(uint32);
	memcpy(tmp, &ndistinct->nitems, sizeof(uint32));
	tmp += sizeof(uint32);

	/*
	 * store number of attributes and attribute numbers for each entry
	 */
	for (i = 0; i < ndistinct->nitems; i++)
	{
		MVNDistinctItem item = ndistinct->items[i];
		int			nmembers = bms_num_members(item.attrs);
		int			x;

		memcpy(tmp, &item.ndistinct, sizeof(double));
		tmp += sizeof(double);
		memcpy(tmp, &nmembers, sizeof(int));
		tmp += sizeof(int);

		x = -1;
		while ((x = bms_next_member(item.attrs, x)) >= 0)
		{
			AttrNumber	value = (AttrNumber) x;

			memcpy(tmp, &value, sizeof(AttrNumber));
			tmp += sizeof(AttrNumber);
		}

		/* protect against overflows */
		Assert(tmp <= ((char *) output + len));
	}

	/* check we used exactly the expected space */
	Assert(tmp == ((char *) output + len));

	return output;
}