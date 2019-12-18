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
 char* NICHOST ; 
 char* host ; 
 int optset ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void getwhoisserver(int argc, char **argv)
{
	int i = 1;

    while(i < argc)
	{
		if (!strcmp(argv[i], "-h"))
		{
			if (i + 2 < argc)
			{
				host = argv[i +1];
				optset = i + 1;
			}
			else
			{
				optset = argc;
			}
			return;
		}
		i++;
	}
	host = NICHOST;
	optset = 1;
}