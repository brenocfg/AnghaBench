#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * cp_str; struct TYPE_8__* cp_next; } ;
typedef  TYPE_2__ compl_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_10__ {int cp_flags; TYPE_2__* cp_next; int /*<<< orphan*/ * cp_str; } ;
struct TYPE_7__ {scalar_t__ col; } ;
struct TYPE_9__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int ORIGINAL_TEXT ; 
 int PTR2CHAR (int /*<<< orphan*/ *) ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 scalar_t__ compl_col ; 
 TYPE_2__* compl_first_match ; 
 int /*<<< orphan*/ * compl_leader ; 
 TYPE_5__* compl_shown_match ; 
 TYPE_4__* curwin ; 
 int /*<<< orphan*/  ins_compl_addleader (int) ; 
 scalar_t__ ins_compl_equal (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ins_compl_addfrommatch()
{
    char_u	*p;
    int		len = (int)curwin->w_cursor.col - (int)compl_col;
    int		c;
    compl_T	*cp;

    p = compl_shown_match->cp_str;
    if ((int)STRLEN(p) <= len)   /* the match is too short */
    {
	/* When still at the original match use the first entry that matches
	 * the leader. */
	if (compl_shown_match->cp_flags & ORIGINAL_TEXT)
	{
	    p = NULL;
	    for (cp = compl_shown_match->cp_next; cp != NULL
				 && cp != compl_first_match; cp = cp->cp_next)
	    {
		if (compl_leader == NULL
			|| ins_compl_equal(cp, compl_leader,
						   (int)STRLEN(compl_leader)))
		{
		    p = cp->cp_str;
		    break;
		}
	    }
	    if (p == NULL || (int)STRLEN(p) <= len)
		return;
	}
	else
	    return;
    }
    p += len;
    c = PTR2CHAR(p);
    ins_compl_addleader(c);
}