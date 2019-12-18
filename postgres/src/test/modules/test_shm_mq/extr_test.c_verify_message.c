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
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
verify_message(Size origlen, char *origdata, Size newlen, char *newdata)
{
	Size		i;

	if (origlen != newlen)
		ereport(ERROR,
				(errmsg("message corrupted"),
				 errdetail("The original message was %zu bytes but the final message is %zu bytes.",
						   origlen, newlen)));

	for (i = 0; i < origlen; ++i)
		if (origdata[i] != newdata[i])
			ereport(ERROR,
					(errmsg("message corrupted"),
					 errdetail("The new and original messages differ at byte %zu of %zu.", i, origlen)));
}