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
typedef  scalar_t__ pgoff_t ;
struct TYPE_5__ {scalar_t__ filePos; scalar_t__ hasSeek; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_6__ {int /*<<< orphan*/  FH; } ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ ftello (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_warning (char*) ; 

__attribute__((used)) static pgoff_t
_getFilePos(ArchiveHandle *AH, lclContext *ctx)
{
	pgoff_t		pos;

	if (ctx->hasSeek)
	{
		/*
		 * Prior to 1.7 (pg7.3) we relied on the internally maintained
		 * pointer.  Now we rely on ftello() always, unless the file has been
		 * found to not support it.  For debugging purposes, print a warning
		 * if the internal pointer disagrees, so that we're more likely to
		 * notice if something's broken about the internal position tracking.
		 */
		pos = ftello(AH->FH);
		if (pos < 0)
			fatal("could not determine seek position in archive file: %m");

		if (pos != ctx->filePos)
			pg_log_warning("ftell mismatch with expected position -- ftell used");
	}
	else
		pos = ctx->filePos;
	return pos;
}