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
typedef  int /*<<< orphan*/  win_T ;
typedef  int /*<<< orphan*/  tabpage_T ;
typedef  scalar_t__ linenr_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  buf_T ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int PyInt ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int OK ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_BadArgument () ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  RAISE_DELETE_LINE_FAIL ; 
 int /*<<< orphan*/  RAISE_REPLACE_LINE_FAIL ; 
 int /*<<< orphan*/  RAISE_UNDO_FAIL ; 
 char* StringToLine (int /*<<< orphan*/ *) ; 
 scalar_t__ VimTryEnd () ; 
 int /*<<< orphan*/  VimTryStart () ; 
 int /*<<< orphan*/  changed_bytes (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cursor_col () ; 
 int /*<<< orphan*/ * curbuf ; 
 int /*<<< orphan*/  deleted_lines_mark (scalar_t__,long) ; 
 scalar_t__ ml_delete (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ml_replace (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  py_fix_cursor (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  restore_win_for_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_to_win_for_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ u_savedel (scalar_t__,long) ; 
 scalar_t__ u_savesub (scalar_t__) ; 
 int /*<<< orphan*/  vim_free (char*) ; 

__attribute__((used)) static int
SetBufferLine(buf_T *buf, PyInt n, PyObject *line, PyInt *len_change)
{
    buf_T	*save_curbuf = NULL;
    win_T	*save_curwin = NULL;
    tabpage_T	*save_curtab = NULL;

    /* First of all, we check the type of the supplied Python object.
     * There are three cases:
     *	  1. NULL, or None - this is a deletion.
     *	  2. A string	   - this is a replacement.
     *	  3. Anything else - this is an error.
     */
    if (line == Py_None || line == NULL)
    {
	PyErr_Clear();
	switch_to_win_for_buf(buf, &save_curwin, &save_curtab, &save_curbuf);

	VimTryStart();

	if (u_savedel((linenr_T)n, 1L) == FAIL)
	    RAISE_UNDO_FAIL;
	else if (ml_delete((linenr_T)n, FALSE) == FAIL)
	    RAISE_DELETE_LINE_FAIL;
	else
	{
	    if (buf == curbuf)
		py_fix_cursor((linenr_T)n, (linenr_T)n + 1, (linenr_T)-1);
	    if (save_curbuf == NULL)
		/* Only adjust marks if we managed to switch to a window that
		 * holds the buffer, otherwise line numbers will be invalid. */
		deleted_lines_mark((linenr_T)n, 1L);
	}

	restore_win_for_buf(save_curwin, save_curtab, save_curbuf);

	if (VimTryEnd())
	    return FAIL;

	if (len_change)
	    *len_change = -1;

	return OK;
    }
    else if (PyBytes_Check(line) || PyUnicode_Check(line))
    {
	char	*save = StringToLine(line);

	if (save == NULL)
	    return FAIL;

	VimTryStart();

	/* We do not need to free "save" if ml_replace() consumes it. */
	PyErr_Clear();
	switch_to_win_for_buf(buf, &save_curwin, &save_curtab, &save_curbuf);

	if (u_savesub((linenr_T)n) == FAIL)
	{
	    RAISE_UNDO_FAIL;
	    vim_free(save);
	}
	else if (ml_replace((linenr_T)n, (char_u *)save, FALSE) == FAIL)
	{
	    RAISE_REPLACE_LINE_FAIL;
	    vim_free(save);
	}
	else
	    changed_bytes((linenr_T)n, 0);

	restore_win_for_buf(save_curwin, save_curtab, save_curbuf);

	/* Check that the cursor is not beyond the end of the line now. */
	if (buf == curbuf)
	    check_cursor_col();

	if (VimTryEnd())
	    return FAIL;

	if (len_change)
	    *len_change = 0;

	return OK;
    }
    else
    {
	PyErr_BadArgument();
	return FAIL;
    }
}