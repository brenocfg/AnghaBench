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
typedef  int /*<<< orphan*/  timestamp ;

/* Variables and functions */
 int PGTYPEStimestamp_fmt_asc (int /*<<< orphan*/ *,char*,int,char*) ; 

int
dttofmtasc(timestamp * ts, char *output, int str_len, char *fmtstr)
{
	return PGTYPEStimestamp_fmt_asc(ts, output, str_len, fmtstr);
}