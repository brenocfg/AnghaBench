#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ignore; int /*<<< orphan*/  token; TYPE_1__* state; } ;
struct TYPE_4__ {int lenchartoken; } ;
typedef  TYPE_2__ TParser ;

/* Variables and functions */
 int /*<<< orphan*/  pg_strncasecmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
SpecialTags(TParser *prs)
{
	switch (prs->state->lenchartoken)
	{
		case 8:					/* </script */
			if (pg_strncasecmp(prs->token, "</script", 8) == 0)
				prs->ignore = false;
			break;
		case 7:					/* <script || </style */
			if (pg_strncasecmp(prs->token, "</style", 7) == 0)
				prs->ignore = false;
			else if (pg_strncasecmp(prs->token, "<script", 7) == 0)
				prs->ignore = true;
			break;
		case 6:					/* <style */
			if (pg_strncasecmp(prs->token, "<style", 6) == 0)
				prs->ignore = true;
			break;
		default:
			break;
	}
}