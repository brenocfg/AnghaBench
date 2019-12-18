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
 int /*<<< orphan*/  printf (char*,...) ; 

void showhdr(unsigned char *hdr)
{
	int i, j;
	for (j = 0; j < 5; j++)
	{
		for (i = 0; i < 16; i++)
		{
			printf("%02x ", (unsigned int)(hdr[j * 16 + i]));
		}
		printf("   ");
		for (i = 0; i < 16; i++)
		{
			unsigned char d = hdr[j * 16 + i];
			printf("%c", (d >= ' ' && d < 127) ? d : '.');
		}
		printf("\n");
	}
}