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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  bytea ;

/* Variables and functions */
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_verifymbstr (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/ * read_binary_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static text *
read_text_file(const char *filename, int64 seek_offset, int64 bytes_to_read,
			   bool missing_ok)
{
	bytea	   *buf;

	buf = read_binary_file(filename, seek_offset, bytes_to_read, missing_ok);

	if (buf != NULL)
	{
		/* Make sure the input is valid */
		pg_verifymbstr(VARDATA(buf), VARSIZE(buf) - VARHDRSZ, false);

		/* OK, we can cast it to text safely */
		return (text *) buf;
	}
	else
		return NULL;
}