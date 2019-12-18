#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNTRANSLATABLE_CHARACTER ; 
 int /*<<< orphan*/  ERROR ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pg_enc2name_tbl ; 
 int pg_encoding_mblen (int,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

void
report_untranslatable_char(int src_encoding, int dest_encoding,
						   const char *mbstr, int len)
{
	int			l = pg_encoding_mblen(src_encoding, mbstr);
	char		buf[8 * 5 + 1];
	char	   *p = buf;
	int			j,
				jlimit;

	jlimit = Min(l, len);
	jlimit = Min(jlimit, 8);	/* prevent buffer overrun */

	for (j = 0; j < jlimit; j++)
	{
		p += sprintf(p, "0x%02x", (unsigned char) mbstr[j]);
		if (j < jlimit - 1)
			p += sprintf(p, " ");
	}

	ereport(ERROR,
			(errcode(ERRCODE_UNTRANSLATABLE_CHARACTER),
			 errmsg("character with byte sequence %s in encoding \"%s\" has no equivalent in encoding \"%s\"",
					buf,
					pg_enc2name_tbl[src_encoding].name,
					pg_enc2name_tbl[dest_encoding].name)));
}