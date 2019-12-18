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

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 scalar_t__ palloc (scalar_t__) ; 

text *
copytext(text *t)
{
	/*
	 * VARSIZE is the total size of the struct in bytes.
	 */
	text	   *new_t = (text *) palloc(VARSIZE(t));

	SET_VARSIZE(new_t, VARSIZE(t));

	/*
	 * VARDATA is a pointer to the data region of the struct.
	 */
	memcpy((void *) VARDATA(new_t), /* destination */
		   (void *) VARDATA(t), /* source */
		   VARSIZE(t) - VARHDRSZ);	/* how many bytes */
	return new_t;
}