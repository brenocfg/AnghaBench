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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  bitmapword ;
struct TYPE_3__ {int nwords; scalar_t__* words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,int) ; 

uint32
bms_hash_value(const Bitmapset *a)
{
	int			lastword;

	if (a == NULL)
		return 0;				/* All empty sets hash to 0 */
	for (lastword = a->nwords; --lastword >= 0;)
	{
		if (a->words[lastword] != 0)
			break;
	}
	if (lastword < 0)
		return 0;				/* All empty sets hash to 0 */
	return DatumGetUInt32(hash_any((const unsigned char *) a->words,
								   (lastword + 1) * sizeof(bitmapword)));
}