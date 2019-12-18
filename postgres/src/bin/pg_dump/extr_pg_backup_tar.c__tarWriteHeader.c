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
struct TYPE_3__ {int /*<<< orphan*/  tarFH; int /*<<< orphan*/  fileLen; int /*<<< orphan*/  targetFile; } ;
typedef  TYPE_1__ TAR_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ERROR_EXIT ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tarCreateHeader (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_tarWriteHeader(TAR_MEMBER *th)
{
	char		h[512];

	tarCreateHeader(h, th->targetFile, NULL, th->fileLen,
					0600, 04000, 02000, time(NULL));

	/* Now write the completed header. */
	if (fwrite(h, 1, 512, th->tarFH) != 512)
		WRITE_ERROR_EXIT;
}