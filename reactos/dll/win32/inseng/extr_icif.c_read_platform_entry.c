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
struct inf_section {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_ALL ; 
 int /*<<< orphan*/  PLATFORM_MILLEN ; 
 int /*<<< orphan*/  PLATFORM_NT4 ; 
 int /*<<< orphan*/  PLATFORM_NT5 ; 
 int /*<<< orphan*/  PLATFORM_WIN98 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* next_part (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  section_get_str (struct inf_section*,char*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static BOOL read_platform_entry(struct inf_section *section, DWORD *ret_platform)
{
    DWORD platform = PLATFORM_ALL;
    char *line, *str, *next;

    if (!section_get_str(section, "Platform", &line, NULL))
        return FALSE;
    if (!line) goto done;

    platform = 0;
    str = line;
    do
    {
        next = next_part(&str, TRUE);

        if (strcasecmp(str, "Win95") == 0)
            platform |= PLATFORM_WIN98;
        else if (strcasecmp(str, "Win98") == 0)
            platform |= PLATFORM_WIN98;
        else if (strcasecmp(str, "NT4") == 0)
            platform |= PLATFORM_NT4;
        else if (strcasecmp(str, "NT5") == 0)
            platform |= PLATFORM_NT5;
        else if (strcasecmp(str, "NT4Alpha") == 0)
            platform |= PLATFORM_NT4;
        else if (strcasecmp(str, "NT5Alpha") == 0)
            platform |= PLATFORM_NT5;
        else if (strcasecmp(str, "Millen") == 0)
            platform |= PLATFORM_MILLEN;
        else
            FIXME("Unknown platform: %s\n", debugstr_a(str));

        str = next;
    } while (str);

done:
    heap_free(line);
    *ret_platform = platform;
    return TRUE;
}