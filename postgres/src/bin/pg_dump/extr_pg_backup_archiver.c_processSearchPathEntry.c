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
struct TYPE_7__ {int /*<<< orphan*/  defn; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_6__ {int /*<<< orphan*/  searchpath; } ;
struct TYPE_8__ {TYPE_1__ public; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  pg_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
processSearchPathEntry(ArchiveHandle *AH, TocEntry *te)
{
	/*
	 * te->defn should contain a command to set search_path.  We just copy it
	 * verbatim for use later.
	 */
	AH->public.searchpath = pg_strdup(te->defn);
}