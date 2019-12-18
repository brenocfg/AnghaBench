#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* replaceTo; int replacelen; struct TYPE_4__* nextChar; } ;
typedef  TYPE_1__ TrieChar ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static TrieChar *
placeChar(TrieChar *node, const unsigned char *str, int lenstr,
		  const char *replaceTo, int replacelen)
{
	TrieChar   *curnode;

	if (!node)
		node = (TrieChar *) palloc0(sizeof(TrieChar) * 256);

	Assert(lenstr > 0);			/* else str[0] doesn't exist */

	curnode = node + *str;

	if (lenstr <= 1)
	{
		if (curnode->replaceTo)
			ereport(WARNING,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("duplicate source strings, first one will be used")));
		else
		{
			curnode->replacelen = replacelen;
			curnode->replaceTo = (char *) palloc(replacelen);
			memcpy(curnode->replaceTo, replaceTo, replacelen);
		}
	}
	else
	{
		curnode->nextChar = placeChar(curnode->nextChar, str + 1, lenstr - 1,
									  replaceTo, replacelen);
	}

	return node;
}