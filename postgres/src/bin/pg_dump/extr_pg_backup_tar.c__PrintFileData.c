#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * FH; } ;
typedef  TYPE_1__ lclContext ;
struct TYPE_8__ {scalar_t__ formatData; } ;
typedef  int /*<<< orphan*/  TAR_MEMBER ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ahwrite (char*,int,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  tarClose (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tarOpen (TYPE_2__*,char*,char) ; 
 size_t tarRead (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_PrintFileData(ArchiveHandle *AH, char *filename)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	char		buf[4096];
	size_t		cnt;
	TAR_MEMBER *th;

	if (!filename)
		return;

	th = tarOpen(AH, filename, 'r');
	ctx->FH = th;

	while ((cnt = tarRead(buf, 4095, th)) > 0)
	{
		buf[cnt] = '\0';
		ahwrite(buf, 1, cnt, AH);
	}

	tarClose(AH, th);
}