#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* fSpec; int gzOut; scalar_t__ mode; void* OF; scalar_t__ FH; } ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  PG_BINARY_A ; 
 int /*<<< orphan*/  PG_BINARY_W ; 
 scalar_t__ archModeAppend ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 void* fdopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fileno (scalar_t__) ; 
 void* fopen (char const*,int /*<<< orphan*/ ) ; 
 void* gzdopen (int /*<<< orphan*/ ,char*) ; 
 void* gzopen (char const*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
SetOutput(ArchiveHandle *AH, const char *filename, int compression)
{
	int			fn;

	if (filename)
	{
		if (strcmp(filename, "-") == 0)
			fn = fileno(stdout);
		else
			fn = -1;
	}
	else if (AH->FH)
		fn = fileno(AH->FH);
	else if (AH->fSpec)
	{
		fn = -1;
		filename = AH->fSpec;
	}
	else
		fn = fileno(stdout);

	/* If compression explicitly requested, use gzopen */
#ifdef HAVE_LIBZ
	if (compression != 0)
	{
		char		fmode[14];

		/* Don't use PG_BINARY_x since this is zlib */
		sprintf(fmode, "wb%d", compression);
		if (fn >= 0)
			AH->OF = gzdopen(dup(fn), fmode);
		else
			AH->OF = gzopen(filename, fmode);
		AH->gzOut = 1;
	}
	else
#endif
	{							/* Use fopen */
		if (AH->mode == archModeAppend)
		{
			if (fn >= 0)
				AH->OF = fdopen(dup(fn), PG_BINARY_A);
			else
				AH->OF = fopen(filename, PG_BINARY_A);
		}
		else
		{
			if (fn >= 0)
				AH->OF = fdopen(dup(fn), PG_BINARY_W);
			else
				AH->OF = fopen(filename, PG_BINARY_W);
		}
		AH->gzOut = 0;
	}

	if (!AH->OF)
	{
		if (filename)
			fatal("could not open output file \"%s\": %m", filename);
		else
			fatal("could not open output file: %m");
	}
}