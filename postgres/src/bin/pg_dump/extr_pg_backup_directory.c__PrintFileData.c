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
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  PG_BINARY_R ; 
 size_t ZLIB_OUT_SIZE ; 
 int /*<<< orphan*/  ahwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ cfclose (int) ; 
 int /*<<< orphan*/  cfopen_read (char*,int /*<<< orphan*/ ) ; 
 int cfp ; 
 size_t cfread (char*,size_t,int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pg_malloc (size_t) ; 

__attribute__((used)) static void
_PrintFileData(ArchiveHandle *AH, char *filename)
{
	size_t		cnt;
	char	   *buf;
	size_t		buflen;
	cfp		   *cfp;

	if (!filename)
		return;

	cfp = cfopen_read(filename, PG_BINARY_R);

	if (!cfp)
		fatal("could not open input file \"%s\": %m", filename);

	buf = pg_malloc(ZLIB_OUT_SIZE);
	buflen = ZLIB_OUT_SIZE;

	while ((cnt = cfread(buf, buflen, cfp)))
	{
		ahwrite(buf, 1, cnt, AH);
	}

	free(buf);
	if (cfclose(cfp) !=0)
		fatal("could not close data file: %m");
}