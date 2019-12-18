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
 int /*<<< orphan*/  LOGDIR_NAME_SIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** fp ; 
 int /*<<< orphan*/  logdir ; 
 char* logfilename ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void end_verification_log(unsigned int tid, unsigned nr_anamolies)
{
	FILE *f = fp[tid];
	char logfile[30];
	char path[LOGDIR_NAME_SIZE + 30];
	char separator[] = "/";

	fclose(f);

	if (nr_anamolies == 0) {
		remove(path);
		return;
	}

	sprintf(logfile, logfilename, tid);
	strcpy(path, logdir);
	strcat(path, separator);
	strcat(path, logfile);

	printf("Thread %02d chunk has %d corrupted words. For details check %s\n",
		tid, nr_anamolies, path);
}