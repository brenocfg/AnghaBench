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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* next_part (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  section_get_str (struct inf_section*,char*,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL read_version_entry(struct inf_section *section, DWORD *ret_ver, DWORD *ret_build)
{
    DWORD version = 0;
    DWORD build = 0;
    char *line, *str, *next;

    if (!section_get_str(section, "Version", &line, NULL))
        return FALSE;
    if (!line) goto done;

    str = line;

    next = next_part(&str, TRUE);
    version |= atoi(str) << 16;
    if (!next) goto done;
    str = next;

    next = next_part(&str, TRUE);
    version |= atoi(str) & 0xffff;
    if (!next) goto done;
    str = next;

    next = next_part(&str, TRUE);
    build |= atoi(str) << 16;
    if (!next) goto done;
    str = next;

    next_part(&str, TRUE);
    build |= atoi(str) & 0xffff;

done:
    heap_free(line);
    *ret_ver = version;
    *ret_build = build;
    return TRUE;
}