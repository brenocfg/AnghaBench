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
 unsigned long CKSUM_MAGIC_NUMBER ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fwrite (unsigned long*,int,int,int /*<<< orphan*/ *) ; 

int cs_set_sum(FILE *fp, unsigned long sum, int tagged)
{
	unsigned long magic = CKSUM_MAGIC_NUMBER;

	if(tagged)
		fseek(fp, -8, SEEK_END);
	else
		fseek(fp, 0, SEEK_END);

	if(fwrite(&magic, 1, 4, fp) < 4)
		return 0;
	if(fwrite(&sum, 1, 4, fp) < 4)
		return 0;

	return 1;
}