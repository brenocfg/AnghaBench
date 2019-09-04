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

/* Variables and functions */
 char NUL ; 
 int TEMP_BUF_SIZE ; 
 int /*<<< orphan*/  get_part (char*,int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void
encoding_part(char *font, char *buf)
{
    char    buf1[TEMP_BUF_SIZE];
    char    buf2[TEMP_BUF_SIZE];

    *buf = '\0';

    get_part(font, 13, buf1);
    get_part(font, 14, buf2);

    if (*buf1 != NUL && *buf2 != NUL)
	vim_snprintf(buf, TEMP_BUF_SIZE, "%s-%s", buf1, buf2);
    if (!strcmp(buf, " "))
	strcpy(buf, "-");
}