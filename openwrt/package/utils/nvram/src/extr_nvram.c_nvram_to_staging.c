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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  NVRAM_STAGING ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 char* nvram_find_mtd () ; 
 int nvram_part_size ; 
 int open (char*,int,...) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

int nvram_to_staging(void)
{
	int fdmtd, fdstg, stat;
	char *mtd = nvram_find_mtd();
	char buf[nvram_part_size];

	stat = -1;

	if( (mtd != NULL) && (nvram_part_size > 0) )
	{
		if( (fdmtd = open(mtd, O_RDONLY)) > -1 )
		{
			if( read(fdmtd, buf, sizeof(buf)) == sizeof(buf) )
			{
				if((fdstg = open(NVRAM_STAGING, O_WRONLY | O_CREAT, 0600)) > -1)
				{
					write(fdstg, buf, sizeof(buf));
					fsync(fdstg);
					close(fdstg);

					stat = 0;
				}
			}

			close(fdmtd);
		}
	}

	free(mtd);
	return stat;
}