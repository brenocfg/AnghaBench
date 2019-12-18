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
struct TYPE_3__ {size_t hashm_ovflpoint; size_t* hashm_spares; } ;
typedef  TYPE_1__* HashMetaPage ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 size_t _hash_get_totalbuckets (size_t) ; 

__attribute__((used)) static BlockNumber
bitno_to_blkno(HashMetaPage metap, uint32 ovflbitnum)
{
	uint32		splitnum = metap->hashm_ovflpoint;
	uint32		i;

	/* Convert zero-based bitnumber to 1-based page number */
	ovflbitnum += 1;

	/* Determine the split number for this page (must be >= 1) */
	for (i = 1;
		 i < splitnum && ovflbitnum > metap->hashm_spares[i];
		 i++)
		 /* loop */ ;

	/*
	 * Convert to absolute page number by adding the number of bucket pages
	 * that exist before this split point.
	 */
	return (BlockNumber) (_hash_get_totalbuckets(i) + ovflbitnum);
}