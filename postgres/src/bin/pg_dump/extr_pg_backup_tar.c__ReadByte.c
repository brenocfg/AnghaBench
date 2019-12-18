#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int filePos; int /*<<< orphan*/  FH; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_5__ {scalar_t__ formatData; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 size_t tarRead (unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_ReadByte(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	size_t		res;
	unsigned char c;

	res = tarRead(&c, 1, ctx->FH);
	if (res != 1)
		/* We already would have exited for errors on reads, must be EOF */
		fatal("could not read from input file: end of file");
	ctx->filePos += 1;
	return c;
}