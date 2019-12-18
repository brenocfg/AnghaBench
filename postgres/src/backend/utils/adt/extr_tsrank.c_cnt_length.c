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
typedef  int /*<<< orphan*/  WordEntry ;
typedef  int /*<<< orphan*/  TSVector ;

/* Variables and functions */
 int /*<<< orphan*/ * ARRPTR (int /*<<< orphan*/ ) ; 
 int POSDATALEN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ STRPTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cnt_length(TSVector t)
{
	WordEntry  *ptr = ARRPTR(t),
			   *end = (WordEntry *) STRPTR(t);
	int			len = 0;

	while (ptr < end)
	{
		int			clen = POSDATALEN(t, ptr);

		if (clen == 0)
			len += 1;
		else
			len += clen;

		ptr++;
	}

	return len;
}