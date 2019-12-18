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
typedef  int Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__* LocalRefCount ; 
 int NLocBuffer ; 
 int /*<<< orphan*/  PrintBufferLeakWarning (int) ; 

__attribute__((used)) static void
CheckForLocalBufferLeaks(void)
{
#ifdef USE_ASSERT_CHECKING
	if (LocalRefCount)
	{
		int			RefCountErrors = 0;
		int			i;

		for (i = 0; i < NLocBuffer; i++)
		{
			if (LocalRefCount[i] != 0)
			{
				Buffer		b = -i - 1;

				PrintBufferLeakWarning(b);
				RefCountErrors++;
			}
		}
		Assert(RefCountErrors == 0);
	}
#endif
}