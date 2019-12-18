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
typedef  scalar_t__ Oid ;

/* Variables and functions */

__attribute__((used)) static void
getOidListDiff(Oid *list1, int *nlist1, Oid *list2, int *nlist2)
{
	int			in1,
				in2,
				out1,
				out2;

	in1 = in2 = out1 = out2 = 0;
	while (in1 < *nlist1 && in2 < *nlist2)
	{
		if (list1[in1] == list2[in2])
		{
			/* skip over duplicates */
			in1++;
			in2++;
		}
		else if (list1[in1] < list2[in2])
		{
			/* list1[in1] is not in list2 */
			list1[out1++] = list1[in1++];
		}
		else
		{
			/* list2[in2] is not in list1 */
			list2[out2++] = list2[in2++];
		}
	}

	/* any remaining list1 entries are not in list2 */
	while (in1 < *nlist1)
	{
		list1[out1++] = list1[in1++];
	}

	/* any remaining list2 entries are not in list1 */
	while (in2 < *nlist2)
	{
		list2[out2++] = list2[in2++];
	}

	*nlist1 = out1;
	*nlist2 = out2;
}