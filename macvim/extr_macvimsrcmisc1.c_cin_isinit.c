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
typedef  int /*<<< orphan*/  skip ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ cin_ends_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cin_skipcomment (int /*<<< orphan*/ *) ; 
 scalar_t__ cin_starts_with (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ml_get_curline () ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
cin_isinit(void)
{
    char_u	*s;
    static char *skip[] = {"static", "public", "protected", "private"};

    s = cin_skipcomment(ml_get_curline());

    if (cin_starts_with(s, "typedef"))
	s = cin_skipcomment(s + 7);

    for (;;)
    {
	int i, l;

	for (i = 0; i < (int)(sizeof(skip) / sizeof(char *)); ++i)
	{
	    l = (int)strlen(skip[i]);
	    if (cin_starts_with(s, skip[i]))
	    {
		s = cin_skipcomment(s + l);
		l = 0;
		break;
	    }
	}
	if (l != 0)
	    break;
    }

    if (cin_starts_with(s, "enum"))
	return TRUE;

    if (cin_ends_in(s, (char_u *)"=", (char_u *)"{"))
	return TRUE;

    return FALSE;
}