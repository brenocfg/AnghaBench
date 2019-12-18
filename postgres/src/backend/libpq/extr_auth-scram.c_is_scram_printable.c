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

/* Variables and functions */

__attribute__((used)) static bool
is_scram_printable(char *p)
{
	/*------
	 * Printable characters, as defined by SCRAM spec: (RFC 5802)
	 *
	 *	printable		= %x21-2B / %x2D-7E
	 *					  ;; Printable ASCII except ",".
	 *					  ;; Note that any "printable" is also
	 *					  ;; a valid "value".
	 *------
	 */
	for (; *p; p++)
	{
		if (*p < 0x21 || *p > 0x7E || *p == 0x2C /* comma */ )
			return false;
	}
	return true;
}