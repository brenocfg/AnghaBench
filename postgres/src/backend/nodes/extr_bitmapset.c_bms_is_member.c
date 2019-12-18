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
typedef  int bitmapword ;
struct TYPE_3__ {int nwords; int* words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int BITNUM (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int WORDNUM (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

bool
bms_is_member(int x, const Bitmapset *a)
{
	int			wordnum,
				bitnum;

	/* XXX better to just return false for x<0 ? */
	if (x < 0)
		elog(ERROR, "negative bitmapset member not allowed");
	if (a == NULL)
		return false;
	wordnum = WORDNUM(x);
	bitnum = BITNUM(x);
	if (wordnum >= a->nwords)
		return false;
	if ((a->words[wordnum] & ((bitmapword) 1 << bitnum)) != 0)
		return true;
	return false;
}