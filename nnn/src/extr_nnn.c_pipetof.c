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
 scalar_t__ CMD_LEN_MAX ; 
 scalar_t__ fgets (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* g_buf ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 

__attribute__((used)) static void pipetof(char *cmd, FILE *fout)
{
	FILE *fin = popen(cmd, "r");

	if (fin) {
		while (fgets(g_buf, CMD_LEN_MAX - 1, fin))
			fprintf(fout, "%s", g_buf);
		pclose(fin);
	}
}