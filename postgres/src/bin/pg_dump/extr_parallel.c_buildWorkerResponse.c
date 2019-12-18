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
struct TYPE_7__ {int dumpId; } ;
typedef  TYPE_2__ TocEntry ;
typedef  int /*<<< orphan*/  T_Action ;
struct TYPE_6__ {int n_errors; } ;
struct TYPE_8__ {TYPE_1__ public; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int WORKER_IGNORED_ERRORS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 

__attribute__((used)) static void
buildWorkerResponse(ArchiveHandle *AH, TocEntry *te, T_Action act, int status,
					char *buf, int buflen)
{
	snprintf(buf, buflen, "OK %d %d %d",
			 te->dumpId,
			 status,
			 status == WORKER_IGNORED_ERRORS ? AH->public.n_errors : 0);
}