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
 char* MALLOC (size_t) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *
parse_name(const char *line, size_t *r_offset, size_t line_length)
{
    size_t name_offset = *r_offset;
    size_t name_length;
    char *result;
    
    /* grab all characters until first space */
    while (*r_offset < line_length && !isspace(line[*r_offset]))
        (*r_offset)++;
    name_length = *r_offset - name_offset;
    if (name_length == 0)
        return 0;
    
    /* trim trailing white space */
    while (*r_offset < line_length && isspace(line[*r_offset]))
        (*r_offset)++;
    
    /* allocate result string */
    result = MALLOC(name_length+1);
    memcpy(result, line + name_offset, name_length+1);
    result[name_length] = '\0';
    
    return result;
}