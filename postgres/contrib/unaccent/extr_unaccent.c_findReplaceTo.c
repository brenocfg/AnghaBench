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
struct TYPE_4__ {struct TYPE_4__* nextChar; scalar_t__ replaceTo; } ;
typedef  TYPE_1__ TrieChar ;

/* Variables and functions */

__attribute__((used)) static TrieChar *
findReplaceTo(TrieChar *node, const unsigned char *src, int srclen,
			  int *p_matchlen)
{
	TrieChar   *result = NULL;
	int			matchlen = 0;

	*p_matchlen = 0;			/* prevent uninitialized-variable warnings */

	while (node && matchlen < srclen)
	{
		node = node + src[matchlen];
		matchlen++;

		if (node->replaceTo)
		{
			result = node;
			*p_matchlen = matchlen;
		}

		node = node->nextChar;
	}

	return result;
}