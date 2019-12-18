#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  OF; scalar_t__ gzOut; } ;
struct TYPE_5__ {int /*<<< orphan*/  OF; scalar_t__ gzOut; } ;
typedef  TYPE_1__ OutputContext ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int GZCLOSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fclose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RestoreOutput(ArchiveHandle *AH, OutputContext savedContext)
{
	int			res;

	if (AH->gzOut)
		res = GZCLOSE(AH->OF);
	else
		res = fclose(AH->OF);

	if (res != 0)
		fatal("could not close output file: %m");

	AH->gzOut = savedContext.gzOut;
	AH->OF = savedContext.OF;
}