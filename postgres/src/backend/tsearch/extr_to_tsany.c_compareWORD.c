#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pos; } ;
struct TYPE_4__ {TYPE_1__ pos; int /*<<< orphan*/  len; int /*<<< orphan*/  word; } ;
typedef  TYPE_2__ ParsedWord ;

/* Variables and functions */
 int tsCompareString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
compareWORD(const void *a, const void *b)
{
	int			res;

	res = tsCompareString(
						  ((const ParsedWord *) a)->word, ((const ParsedWord *) a)->len,
						  ((const ParsedWord *) b)->word, ((const ParsedWord *) b)->len,
						  false);

	if (res == 0)
	{
		if (((const ParsedWord *) a)->pos.pos == ((const ParsedWord *) b)->pos.pos)
			return 0;

		res = (((const ParsedWord *) a)->pos.pos > ((const ParsedWord *) b)->pos.pos) ? 1 : -1;
	}

	return res;
}