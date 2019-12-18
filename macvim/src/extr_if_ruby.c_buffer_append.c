#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  colnr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_5__ {long ml_line_count; } ;
struct TYPE_6__ {TYPE_1__ b_ml; } ;
typedef  TYPE_2__ buf_T ;
typedef  int /*<<< orphan*/  aco_save_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NOT_VALID ; 
 long NUM2LONG (int /*<<< orphan*/ ) ; 
 scalar_t__ OK ; 
 char* StringValuePtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appended_lines_mark (long,long) ; 
 int /*<<< orphan*/  aucmd_prepbuf (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  aucmd_restbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  changed () ; 
 TYPE_2__* get_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_append (long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_eIndexError ; 
 int /*<<< orphan*/  rb_raise (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ u_inssub (long) ; 
 int /*<<< orphan*/  update_curbuf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE buffer_append(VALUE self, VALUE num, VALUE str)
{
    buf_T	*buf = get_buf(self);
    char	*line = StringValuePtr(str);
    long	n = NUM2LONG(num);
    aco_save_T	aco;

    if (line == NULL)
    {
	rb_raise(rb_eIndexError, "NULL line");
    }
    else if (n >= 0 && n <= buf->b_ml.ml_line_count)
    {
	/* set curwin/curbuf for "buf" and save some things */
	aucmd_prepbuf(&aco, buf);

	if (u_inssub(n + 1) == OK) {
	    ml_append(n, (char_u *) line, (colnr_T) 0, FALSE);

	    /*  Changes to non-active buffers should properly refresh screen
	     *    SegPhault - 12/20/04 */
	    appended_lines_mark(n, 1L);

	    changed();
	}

	/* restore curwin/curbuf and a few other things */
	aucmd_restbuf(&aco);
	/* Careful: autocommands may have made "buf" invalid! */

	update_curbuf(NOT_VALID);
    }
    else
    {
	rb_raise(rb_eIndexError, "line number %ld out of range", n);
    }
    return str;
}