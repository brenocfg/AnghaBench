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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  dev ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int S_IFBLK ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int nvram_part_size ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ sscanf (char*,char*,int*,int*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,scalar_t__) ; 
 scalar_t__ strstr (char*,char*) ; 

char * nvram_find_mtd(void)
{
	FILE *fp;
	int i, part_size;
	char dev[PATH_MAX];
	char *path = NULL;
	struct stat s;

	if ((fp = fopen("/proc/mtd", "r")))
	{
		while( fgets(dev, sizeof(dev), fp) )
		{
			if( strstr(dev, "nvram") && sscanf(dev, "mtd%d: %08x", &i, &part_size) )
			{
				nvram_part_size = part_size;

				sprintf(dev, "/dev/mtdblock%d", i);
				if( stat(dev, &s) > -1 && (s.st_mode & S_IFBLK) )
				{
					if( (path = (char *) malloc(strlen(dev)+1)) != NULL )
					{
						strncpy(path, dev, strlen(dev)+1);
						break;
					}
				}
			}
		}
		fclose(fp);
	}

	return path;
}