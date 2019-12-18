#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ col; int /*<<< orphan*/  lnum; } ;
typedef  TYPE_2__ pos_T ;
typedef  scalar_t__ colnr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_6__ {int /*<<< orphan*/  lnum; } ;
struct TYPE_8__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 scalar_t__ STRNCMP (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ cin_nocode (int /*<<< orphan*/ *) ; 
 TYPE_3__* curwin ; 
 int /*<<< orphan*/  getvcol (TYPE_3__*,TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ml_get_curline () ; 
 int /*<<< orphan*/ * skiptowhite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skipwhite (int /*<<< orphan*/ *) ; 
 scalar_t__ vim_isIDc (int /*<<< orphan*/ ) ; 
 scalar_t__ vim_iswhite (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cin_first_id_amount()
{
    char_u	*line, *p, *s;
    int		len;
    pos_T	fp;
    colnr_T	col;

    line = ml_get_curline();
    p = skipwhite(line);
    len = (int)(skiptowhite(p) - p);
    if (len == 6 && STRNCMP(p, "static", 6) == 0)
    {
	p = skipwhite(p + 6);
	len = (int)(skiptowhite(p) - p);
    }
    if (len == 6 && STRNCMP(p, "struct", 6) == 0)
	p = skipwhite(p + 6);
    else if (len == 4 && STRNCMP(p, "enum", 4) == 0)
	p = skipwhite(p + 4);
    else if ((len == 8 && STRNCMP(p, "unsigned", 8) == 0)
	    || (len == 6 && STRNCMP(p, "signed", 6) == 0))
    {
	s = skipwhite(p + len);
	if ((STRNCMP(s, "int", 3) == 0 && vim_iswhite(s[3]))
		|| (STRNCMP(s, "long", 4) == 0 && vim_iswhite(s[4]))
		|| (STRNCMP(s, "short", 5) == 0 && vim_iswhite(s[5]))
		|| (STRNCMP(s, "char", 4) == 0 && vim_iswhite(s[4])))
	    p = s;
    }
    for (len = 0; vim_isIDc(p[len]); ++len)
	;
    if (len == 0 || !vim_iswhite(p[len]) || cin_nocode(p))
	return 0;

    p = skipwhite(p + len);
    fp.lnum = curwin->w_cursor.lnum;
    fp.col = (colnr_T)(p - line);
    getvcol(curwin, &fp, &col, NULL, NULL);
    return (int)col;
}