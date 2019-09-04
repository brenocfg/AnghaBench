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
struct Masscan {int dummy; } ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fopen_s (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  masscan_echo (struct Masscan*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy_s (char*,int,char*) ; 

void
masscan_save_state(struct Masscan *masscan)
{
    char filename[512];
    FILE *fp;
    int err;


    strcpy_s(filename, sizeof(filename), "paused.conf");
    fprintf(stderr, "                                   "
                    "                                   \r");
    fprintf(stderr, "saving resume file to: %s\n", filename);

    err = fopen_s(&fp, filename, "wt");
    if (err) {
        perror(filename);
        return;
    }

    
    masscan_echo(masscan, fp, 0);

    fclose(fp);
}