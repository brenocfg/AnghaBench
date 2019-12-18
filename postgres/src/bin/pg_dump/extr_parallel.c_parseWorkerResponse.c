#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dumpId; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_6__ {int n_errors; } ;
struct TYPE_8__ {TYPE_1__ public; } ;
typedef  scalar_t__ DumpId ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 scalar_t__ messageStartsWith (char const*,char*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,scalar_t__*,int*,int*,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
parseWorkerResponse(ArchiveHandle *AH, TocEntry *te,
					const char *msg)
{
	DumpId		dumpId;
	int			nBytes,
				n_errors;
	int			status = 0;

	if (messageStartsWith(msg, "OK "))
	{
		sscanf(msg, "OK %d %d %d%n", &dumpId, &status, &n_errors, &nBytes);

		Assert(dumpId == te->dumpId);
		Assert(nBytes == strlen(msg));

		AH->public.n_errors += n_errors;
	}
	else
		fatal("invalid message received from worker: \"%s\"",
			  msg);

	return status;
}