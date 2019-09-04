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
 scalar_t__ code ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ ntflag ; 
 char* ntin ; 
 char* ntout ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void setntrans(int argc, const char *argv[])
{
	if (argc == 1) {
		ntflag = 0;
		printf("Ntrans off.\n");
		(void) fflush(stdout);
		code = ntflag;
		return;
	}
	ntflag++;
	code = ntflag;
	(void) strncpy(ntin, argv[1], 16);
	ntin[16] = '\0';
	if (argc == 2) {
		ntout[0] = '\0';
		return;
	}
	(void) strncpy(ntout, argv[2], 16);
	ntout[16] = '\0';
}