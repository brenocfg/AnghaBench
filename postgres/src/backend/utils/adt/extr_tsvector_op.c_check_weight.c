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
typedef  int int8 ;
typedef  int /*<<< orphan*/  WordEntryPos ;
typedef  int /*<<< orphan*/  WordEntry ;
typedef  int /*<<< orphan*/  TSVector ;

/* Variables and functions */
 int POSDATALEN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * POSDATAPTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int WEP_GETWEIGHT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_weight(TSVector txt, WordEntry *wptr, int8 weight)
{
	int			len = POSDATALEN(txt, wptr);
	int			num = 0;
	WordEntryPos *ptr = POSDATAPTR(txt, wptr);

	while (len--)
	{
		if (weight & (1 << WEP_GETWEIGHT(*ptr)))
			num++;
		ptr++;
	}
	return num;
}