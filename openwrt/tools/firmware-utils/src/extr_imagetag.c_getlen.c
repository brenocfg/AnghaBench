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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 

size_t getlen(FILE *fp)
{
	size_t retval, curpos;

	if (!fp)
		return 0;

	curpos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	retval = ftell(fp);
	fseek(fp, curpos, SEEK_SET);

	return retval;
}