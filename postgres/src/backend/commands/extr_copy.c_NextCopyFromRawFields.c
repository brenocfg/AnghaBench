#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_8__ {scalar_t__ cur_lineno; char** raw_fields; scalar_t__ csv_mode; TYPE_1__ line_buf; scalar_t__ header_line; int /*<<< orphan*/  binary; } ;
typedef  TYPE_2__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int CopyReadAttributesCSV (TYPE_2__*) ; 
 int CopyReadAttributesText (TYPE_2__*) ; 
 int CopyReadLine (TYPE_2__*) ; 

bool
NextCopyFromRawFields(CopyState cstate, char ***fields, int *nfields)
{
	int			fldct;
	bool		done;

	/* only available for text or csv input */
	Assert(!cstate->binary);

	/* on input just throw the header line away */
	if (cstate->cur_lineno == 0 && cstate->header_line)
	{
		cstate->cur_lineno++;
		if (CopyReadLine(cstate))
			return false;		/* done */
	}

	cstate->cur_lineno++;

	/* Actually read the line into memory here */
	done = CopyReadLine(cstate);

	/*
	 * EOF at start of line means we're done.  If we see EOF after some
	 * characters, we act as though it was newline followed by EOF, ie,
	 * process the line and then exit loop on next iteration.
	 */
	if (done && cstate->line_buf.len == 0)
		return false;

	/* Parse the line into de-escaped field values */
	if (cstate->csv_mode)
		fldct = CopyReadAttributesCSV(cstate);
	else
		fldct = CopyReadAttributesText(cstate);

	*fields = cstate->raw_fields;
	*nfields = fldct;
	return true;
}