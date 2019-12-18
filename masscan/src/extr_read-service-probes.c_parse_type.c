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
typedef  enum SvcP_RecordType { ____Placeholder_SvcP_RecordType } SvcP_RecordType ;

/* Variables and functions */
#define  SvcP_Exclude 138 
#define  SvcP_Fallback 137 
#define  SvcP_Match 136 
#define  SvcP_Ports 135 
#define  SvcP_Probe 134 
#define  SvcP_Rarity 133 
#define  SvcP_Softmatch 132 
#define  SvcP_Sslports 131 
#define  SvcP_Tcpwrappedms 130 
#define  SvcP_Totalwaitms 129 
#define  SvcP_Unknown 128 
 scalar_t__ isspace (char const) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static enum SvcP_RecordType
parse_type(const char *line, size_t *r_offset, size_t line_length)
{
    static const struct {
        const char *name;
        size_t length;
        enum SvcP_RecordType type;
    } name_to_types[] = {
        {"exclude",      7, SvcP_Exclude},
        {"probe",        5, SvcP_Probe},
        {"match",        5, SvcP_Match},
        {"softmatch",    9, SvcP_Softmatch},
        {"ports",        5, SvcP_Ports},
        {"sslports",     8, SvcP_Sslports},
        {"totalwaitms", 11, SvcP_Totalwaitms},
        {"tcpwrappedms",12, SvcP_Tcpwrappedms},
        {"rarity",       6, SvcP_Rarity},
        {"fallback",     8, SvcP_Fallback},
        {0, SvcP_Unknown}
    };

    size_t i;
    size_t offset = *r_offset;
    size_t name_length;
    size_t name_offset;
    enum SvcP_RecordType result;
    
    /* find length of command name */
    name_offset = offset;
    while (offset < line_length && !isspace(line[offset]))
        offset++; /* name = all non-space chars until first space */
    name_length = offset - name_offset;
    while (offset < line_length && isspace(line[offset]))
        offset++; /* trim whitespace after name */
    *r_offset = offset;
    
    /* Lookup the command name */
    for (i=0; name_to_types[i].name; i++) {
        if (name_length != name_to_types[i].length)
            continue;
        if (strncasecmp(line+name_offset, name_to_types[i].name, name_length) == 0) {
            break;
        }
    }
    result = name_to_types[i].type;
    
    /* return the type */
    return result;
}