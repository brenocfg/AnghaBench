#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ filename; } ;
typedef  TYPE_2__ lclTocEntry ;
struct TYPE_10__ {scalar_t__ formatData; } ;
typedef  TYPE_3__ TocEntry ;
struct TYPE_8__ {scalar_t__ verbose; } ;
struct TYPE_11__ {TYPE_1__ public; } ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ahprintf (TYPE_4__*,char*,scalar_t__) ; 

__attribute__((used)) static void
_PrintExtraToc(ArchiveHandle *AH, TocEntry *te)
{
	lclTocEntry *tctx = (lclTocEntry *) te->formatData;

	if (AH->public.verbose && tctx->filename)
		ahprintf(AH, "-- File: %s\n", tctx->filename);
}