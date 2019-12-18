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
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int cs_is_tagged(FILE *fp)
{
	char buf[8];

	fseek(fp, -8, SEEK_END);
	fread(buf, 8, 1, fp);
	if(*(unsigned long*)buf == CKSUM_MAGIC_NUMBER)
		return 1;
	return 0;
}