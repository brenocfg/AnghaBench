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
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 char* VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ palloc (scalar_t__) ; 

__attribute__((used)) static text *
makeitem(char *str, int len, char flag)
{
	text	   *item;

	item = (text *) palloc(VARHDRSZ + len + 1);
	SET_VARSIZE(item, VARHDRSZ + len + 1);

	*VARDATA(item) = flag;

	if (str && len > 0)
		memcpy(VARDATA(item) + 1, str, len);

	return item;
}