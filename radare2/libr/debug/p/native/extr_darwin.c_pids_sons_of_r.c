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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cons_printf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,int*,char*,char*,int*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  pids_cmdline (int,char*) ; 
 scalar_t__ readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

int pids_sons_of_r(int pid, int recursive, int limit) {
        int p, mola, tmp, n = 0;
        FILE *fd;
        char tmp3[8];
        char buf[128];
        char tmp2[1024];
        struct dirent *file;
        DIR *dh;
       
        if (pid < 1)
	       return false;
	dh = opendir ("/proc/");
	if (!dh) {
                return false;
	}

        while ((file = (struct dirent *)readdir (dh))) {
                p = atoi (file->d_name);
                if (p) {
                        sprintf (buf,"/proc/%s/stat", file->d_name);
                        fd = fopen (buf, "r");
                        if (fd) {
                                mola = 0;
                                fscanf (fd,"%d %s %s %d",
                                        &tmp, tmp2, tmp3, &mola);
                                if (mola == pid) {
                                        pids_cmdline (p, tmp2);
                                        //for(i=0; i<recursive*2;i++)
                                        //      printf(" ");
                                        cons_printf (" `- %d : %s (%s)\n",
						p, tmp2, (tmp3[0]=='S')?
						"sleeping":(tmp3[0]=='T')?
						"stopped":"running");
                                        n++;
                                        if (recursive<limit) {
                                                n += pids_sons_of_r (p, recursive+1, limit);
					}
                                }
                        }
                        fclose (fd);
                }
        }
	closedir (dh);
        return n;
}