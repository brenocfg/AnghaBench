#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct config_generic {int flags; char* name; } ;
typedef  int /*<<< orphan*/  StringInfoData ;

/* Variables and functions */
 int GUC_REPORT ; 
 char* _ShowOption (struct config_generic*,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ reporting_enabled ; 

__attribute__((used)) static void
ReportGUCOption(struct config_generic *record)
{
	if (reporting_enabled && (record->flags & GUC_REPORT))
	{
		char	   *val = _ShowOption(record, false);
		StringInfoData msgbuf;

		pq_beginmessage(&msgbuf, 'S');
		pq_sendstring(&msgbuf, record->name);
		pq_sendstring(&msgbuf, val);
		pq_endmessage(&msgbuf);

		pfree(val);
	}
}