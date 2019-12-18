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
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  atol (char*) ; 
 int /*<<< orphan*/  md_count ; 
 int /*<<< orphan*/  md_fail_percent ; 
 char* md_failstring ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void parseit(void)
{
    char *semi = strchr(md_failstring, ';');
    char *atsign;

    if (semi != NULL)
        *semi++ = '\0';

    /* Get the count (atol will stop at the @ if there), and percentage */
    md_count = atol(md_failstring);
    atsign = strchr(md_failstring, '@');
    md_fail_percent = atsign == NULL ? 0 : atoi(atsign + 1);

    if (semi != NULL)
        md_failstring = semi;
}