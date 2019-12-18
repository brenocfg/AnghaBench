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
 char* _strdup (char const*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 

char *
STRDUP(const char *str)
{
#if defined(WIN32)
    char *p = _strdup(str);
#else
    char *p = strdup(str);
#endif
    
    if (p == NULL && str != NULL) {
        fprintf(stderr, "[-] out of memory, aborting\n");
        abort();
    }
    
    return p;
}