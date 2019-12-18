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
typedef  scalar_t__ int32 ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ palloc (scalar_t__) ; 

text *
concat_text(text *arg1, text *arg2)
{
	int32		arg1_size = VARSIZE(arg1) - VARHDRSZ;
	int32		arg2_size = VARSIZE(arg2) - VARHDRSZ;
	int32		new_text_size = arg1_size + arg2_size + VARHDRSZ;
	text	   *new_text = (text *) palloc(new_text_size);

	SET_VARSIZE(new_text, new_text_size);
	memcpy(VARDATA(new_text), VARDATA(arg1), arg1_size);
	memcpy(VARDATA(new_text) + arg1_size, VARDATA(arg2), arg2_size);
	return new_text;
}