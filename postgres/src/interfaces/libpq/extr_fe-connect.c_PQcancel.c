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
struct TYPE_3__ {int /*<<< orphan*/  be_key; int /*<<< orphan*/  be_pid; int /*<<< orphan*/  raddr; } ;
typedef  TYPE_1__ PGcancel ;

/* Variables and functions */
 int internal_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

int
PQcancel(PGcancel *cancel, char *errbuf, int errbufsize)
{
	if (!cancel)
	{
		strlcpy(errbuf, "PQcancel() -- no cancel object supplied", errbufsize);
		return false;
	}

	return internal_cancel(&cancel->raddr, cancel->be_pid, cancel->be_key,
						   errbuf, errbufsize);
}