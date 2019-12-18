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
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char* const) ; 
 scalar_t__ strlen (char* const) ; 

char* flatten_cmdline(const char *prog, char* const argv[])
{
    int i;
    SIZE_T argstr_size = 0;
    char *argstr, *p;

    /* Compute space needed for the new string, and allocate it */
    argstr_size += strlen(prog) + 3; // 3 == 2 quotes between 'prog', and 1 space
    for(i = 0; argv[i] != NULL; ++i)
    {
        argstr_size += strlen(argv[i]) + 1; // 1 for space
    }
    argstr = HeapAlloc(GetProcessHeap(), 0, (argstr_size + 1) * sizeof(CHAR));
    if (argstr == NULL)
    {
        ERR("ERROR: Not enough memory\n");
        return NULL;
    }

    /* Copy the contents and NULL-terminate the string */
    p = argstr;
    strcpy(p, "\"");    // Open quote
    strcat(p, prog);
    strcat(p, "\" ");   // Close quote + space
    p += strlen(p);
    for(i = 0; argv[i] != NULL; ++i)
    {
        strcpy(p, argv[i]);
        p += strlen(argv[i]);
        *p++ = ' ';
    }
    *p = '\0';

    return argstr;
}