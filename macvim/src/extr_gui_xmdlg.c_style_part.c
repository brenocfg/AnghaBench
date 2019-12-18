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
 int TEMP_BUF_SIZE ; 
 int /*<<< orphan*/  get_part (char*,int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,char*,...) ; 

__attribute__((used)) static void
style_part(char *font, char *buf)
{
    char    buf2[TEMP_BUF_SIZE];
    char    buf3[TEMP_BUF_SIZE];

    get_part(font, 3, buf3);
    get_part(font, 5, buf2);

    if (!strcmp(buf2, "normal") && !strcmp(buf2, "Normal")
						   && !strcmp(buf2, "NORMAL"))
	vim_snprintf(buf, TEMP_BUF_SIZE, "%s %s", buf3, buf2);
    else
	strcpy(buf, buf3);

    get_part(font, 6, buf2);

    if (buf2[0] != '\0')
	vim_snprintf(buf3, TEMP_BUF_SIZE, "%s %s", buf, buf2);
    else
	strcpy(buf3, buf);

    get_part(font, 4, buf2);

    if (!strcmp(buf2, "o") || !strcmp(buf2, "O"))
	vim_snprintf(buf, TEMP_BUF_SIZE, "%s oblique", buf3);
    else if (!strcmp(buf2, "i") || !strcmp(buf2, "I"))
	vim_snprintf(buf, TEMP_BUF_SIZE, "%s italic", buf3);

    if (!strcmp(buf, " "))
	strcpy(buf, "-");
}