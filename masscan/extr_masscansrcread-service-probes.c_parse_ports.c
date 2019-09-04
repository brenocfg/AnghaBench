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
struct RangeList {int /*<<< orphan*/  member_0; } ;
struct NmapServiceProbeList {char* filename; int line_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,unsigned int) ; 
 char* rangelist_parse_ports (struct RangeList*,char const*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_remove_all (struct RangeList*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct RangeList
parse_ports(struct NmapServiceProbeList *list, const char *line, size_t offset, size_t line_length)
{
    /* Examples:
        Exclude 53,T:9100,U:30000-40000
        ports 21,43,110,113,199,505,540,1248,5432,30444
        ports 111,4045,32750-32810,38978
        sslports 443
     */
    unsigned is_error = 0;
    const char *p;
    struct RangeList ranges = {0};

    UNUSEDPARM(line_length);
    
    p = rangelist_parse_ports(&ranges, line + offset, &is_error, 0);
    
    if (is_error) {
        fprintf(stderr, "%s:%u:%u: bad port spec\n", list->filename, list->line_number, (unsigned)(p-line));
        rangelist_remove_all(&ranges);
    }
    
    return ranges;
}