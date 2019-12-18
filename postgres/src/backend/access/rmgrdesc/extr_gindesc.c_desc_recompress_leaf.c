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
typedef  int uint8 ;
typedef  int uint16 ;
struct TYPE_3__ {int nactions; } ;
typedef  TYPE_1__ ginxlogRecompressDataLeaf ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  GinPostingList ;

/* Variables and functions */
#define  GIN_SEGMENT_ADDITEMS 131 
#define  GIN_SEGMENT_DELETE 130 
#define  GIN_SEGMENT_INSERT 129 
#define  GIN_SEGMENT_REPLACE 128 
 int /*<<< orphan*/  SHORTALIGN (int) ; 
 int SizeOfGinPostingList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 

__attribute__((used)) static void
desc_recompress_leaf(StringInfo buf, ginxlogRecompressDataLeaf *insertData)
{
	int			i;
	char	   *walbuf = ((char *) insertData) + sizeof(ginxlogRecompressDataLeaf);

	appendStringInfo(buf, " %d segments:", (int) insertData->nactions);

	for (i = 0; i < insertData->nactions; i++)
	{
		uint8		a_segno = *((uint8 *) (walbuf++));
		uint8		a_action = *((uint8 *) (walbuf++));
		uint16		nitems = 0;
		int			newsegsize = 0;

		if (a_action == GIN_SEGMENT_INSERT ||
			a_action == GIN_SEGMENT_REPLACE)
		{
			newsegsize = SizeOfGinPostingList((GinPostingList *) walbuf);
			walbuf += SHORTALIGN(newsegsize);
		}

		if (a_action == GIN_SEGMENT_ADDITEMS)
		{
			memcpy(&nitems, walbuf, sizeof(uint16));
			walbuf += sizeof(uint16);
			walbuf += nitems * sizeof(ItemPointerData);
		}

		switch (a_action)
		{
			case GIN_SEGMENT_ADDITEMS:
				appendStringInfo(buf, " %d (add %d items)", a_segno, nitems);
				break;
			case GIN_SEGMENT_DELETE:
				appendStringInfo(buf, " %d (delete)", a_segno);
				break;
			case GIN_SEGMENT_INSERT:
				appendStringInfo(buf, " %d (insert)", a_segno);
				break;
			case GIN_SEGMENT_REPLACE:
				appendStringInfo(buf, " %d (replace)", a_segno);
				break;
			default:
				appendStringInfo(buf, " %d unknown action %d ???", a_segno, a_action);
				/* cannot decode unrecognized actions further */
				return;
		}
	}
}