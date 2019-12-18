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
struct TYPE_3__ {scalar_t__ OF; scalar_t__ gzOut; int /*<<< orphan*/  (* ClosePtr ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int GZCLOSE (scalar_t__) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fclose (scalar_t__) ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
CloseArchive(Archive *AHX)
{
	int			res = 0;
	ArchiveHandle *AH = (ArchiveHandle *) AHX;

	AH->ClosePtr(AH);

	/* Close the output */
	if (AH->gzOut)
		res = GZCLOSE(AH->OF);
	else if (AH->OF != stdout)
		res = fclose(AH->OF);

	if (res != 0)
		fatal("could not close output file: %m");
}