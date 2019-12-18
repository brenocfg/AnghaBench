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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int READ_BUFF_SIZE ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t copy_file(FILE * to, FILE * from)
{
	size_t i, fsize = 0;
	uint8_t buf[READ_BUFF_SIZE];

	while (!feof(from) && !ferror(from))
	{
		i = fread(buf, sizeof(uint8_t), READ_BUFF_SIZE, from);
		if (i > 0)
		{
			fsize += i;
			fwrite(buf, sizeof(uint8_t), i, to);
		}
	}
	return fsize;
}