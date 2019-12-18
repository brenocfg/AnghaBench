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
typedef  int /*<<< orphan*/  line ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  dir ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 scalar_t__ ispunct (char) ; 
 int /*<<< orphan*/  masscan_set_parameter (struct Masscan*,char*,char*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  trim (char*,int) ; 

void
masscan_read_config_file(struct Masscan *masscan, const char *filename)
{
    FILE *fp;
    errno_t err;
    char line[65536];

    err = fopen_s(&fp, filename, "rt");
    if (err) {
        char dir[512];
        perror(filename);
        getcwd(dir, sizeof(dir));
        fprintf(stderr, "cwd = %s\n", dir);
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        char *name;
        char *value;

        trim(line, sizeof(line));

        if (ispunct(line[0] & 0xFF) || line[0] == '\0')
            continue;

        name = line;
        value = strchr(line, '=');
        if (value == NULL)
            continue;
        *value = '\0';
        value++;
        trim(name, sizeof(line));
        trim(value, sizeof(line));

        masscan_set_parameter(masscan, name, value);
    }

    fclose(fp);
}