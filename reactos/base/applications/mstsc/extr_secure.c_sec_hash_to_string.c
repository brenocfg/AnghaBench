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
typedef  int uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
sec_hash_to_string(char *out, int out_size, uint8 * in, int in_size)
{
	int k;
	memset(out, 0, out_size);
	for (k = 0; k < in_size; k++, out += 2)
	{
		sprintf(out, "%.2x", in[k]);
	}
}