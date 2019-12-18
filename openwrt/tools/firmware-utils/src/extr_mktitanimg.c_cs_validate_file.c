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
 int /*<<< orphan*/  cs_calc_sum (int /*<<< orphan*/ *,unsigned long*,int) ; 
 int /*<<< orphan*/  cs_get_sum (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  cs_is_tagged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 

int cs_validate_file(char *filename)
{
	FILE *pFile = NULL;
	unsigned long sum = 0, res = 0;

	if((pFile = fopen(filename, "r")) == NULL)
		return 0;

	if(!cs_is_tagged(pFile))
	{
		fclose(pFile);
		return 0;
	}
	if(!cs_calc_sum(pFile, &sum, 1))
	{
		fclose(pFile);
		return 0;
	}
	cs_get_sum(pFile, &res);
	fclose(pFile);

	if(sum != res)
		return 0;
	return 1;
}