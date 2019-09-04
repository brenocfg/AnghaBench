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

/* Variables and functions */
 int /*<<< orphan*/  argbase ; 
 int /*<<< orphan*/  argbuf ; 
 int /*<<< orphan*/  line ; 
 scalar_t__ margc ; 
 char** margv ; 
 scalar_t__ slrflag ; 
 int /*<<< orphan*/  slurpstring () ; 
 int /*<<< orphan*/  stringbase ; 

void makeargv(void)
{
	const char **argp;

	margc = 0;
	argp = margv;
	stringbase = line;		/* scan from first of buffer */
	argbase = argbuf;		/* store from first of buffer */
	slrflag = 0;
	while ((*argp++ = slurpstring()))
		margc++;
}