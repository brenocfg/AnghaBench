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
 char* app_malloc (size_t,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const char *newline_escape_filename(const char *file, int * backslash)
{
    size_t i, e = 0, length = strlen(file), newline_count = 0, mem_len = 0;
    char *file_cpy = NULL;

    for (i = 0; i < length; i++)
        if (file[i] == '\n')
            newline_count++;

    mem_len = length + newline_count + 1;
    file_cpy = app_malloc(mem_len, file);
    i = 0;

    while(e < length) {
        const char c = file[e];
        if (c == '\n') {
            file_cpy[i++] = '\\';
            file_cpy[i++] = 'n';
            *backslash = 1;
        } else {
            file_cpy[i++] = c;
        }
        e++;
    }
    file_cpy[i] = '\0';
    return (const char*)file_cpy;
}