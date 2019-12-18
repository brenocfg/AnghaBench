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
typedef  int uint32 ;
struct TYPE_3__ {int hashm_ovflpoint; int* hashm_spares; } ;
typedef  TYPE_1__* HashMetaPage ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ _hash_get_totalbuckets (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 

uint32
_hash_ovflblkno_to_bitno(HashMetaPage metap, BlockNumber ovflblkno)
{
	uint32		splitnum = metap->hashm_ovflpoint;
	uint32		i;
	uint32		bitnum;

	/* Determine the split number containing this page */
	for (i = 1; i <= splitnum; i++)
	{
		if (ovflblkno <= (BlockNumber) _hash_get_totalbuckets(i))
			break;				/* oops */
		bitnum = ovflblkno - _hash_get_totalbuckets(i);

		/*
		 * bitnum has to be greater than number of overflow page added in
		 * previous split point. The overflow page at this splitnum (i) if any
		 * should start from (_hash_get_totalbuckets(i) +
		 * metap->hashm_spares[i - 1] + 1).
		 */
		if (bitnum > metap->hashm_spares[i - 1] &&
			bitnum <= metap->hashm_spares[i])
			return bitnum - 1;	/* -1 to convert 1-based to 0-based */
	}

	ereport(ERROR,
			(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
			 errmsg("invalid overflow block number %u", ovflblkno)));
	return 0;					/* keep compiler quiet */
}