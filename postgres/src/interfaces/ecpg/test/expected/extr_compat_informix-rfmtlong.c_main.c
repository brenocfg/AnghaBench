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
 int /*<<< orphan*/  ECPGdebug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtlong (int,char*) ; 
 int /*<<< orphan*/  stderr ; 

int
main(void)
{
	ECPGdebug(1, stderr);

	fmtlong(-8494493, "-<<<<,<<<,<<<,<<<");
	fmtlong(-8494493, "################");
	fmtlong(-8494493, "+++$$$$$$$$$$$$$.##");
	fmtlong(-8494493, "(&,&&&,&&&,&&&.)");
	fmtlong(-8494493, "<<<<,<<<,<<<,<<<");
	fmtlong(-8494493, "$************.**");
	fmtlong(-8494493, "---$************.**");
	fmtlong(-8494493, "+-+################");
	fmtlong(-8494493, "abc: ################+-+");
	fmtlong(-8494493, "+<<<<,<<<,<<<,<<<");

	return 0;
}