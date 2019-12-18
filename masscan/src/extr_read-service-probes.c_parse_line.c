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
struct ServiceProbeMatch {int is_softmatch; struct ServiceProbeMatch* next; } ;
struct ServiceProbeFallback {struct ServiceProbeFallback* next; } ;
struct RangeList {int /*<<< orphan*/  count; int /*<<< orphan*/  member_0; } ;
struct NmapServiceProbeList {char* filename; unsigned int line_number; int count; struct NmapServiceProbe** list; int /*<<< orphan*/  exclude; } ;
struct NmapServiceProbe {struct ServiceProbeFallback* fallback; void* rarity; void* tcpwrappedms; void* totalwaitms; struct ServiceProbeMatch* match; int /*<<< orphan*/  sslports; int /*<<< orphan*/  ports; } ;
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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,unsigned int,unsigned int,...) ; 
 scalar_t__ ispunct (char const) ; 
 scalar_t__ isspace (char const) ; 
 struct ServiceProbeFallback* parse_fallback (struct NmapServiceProbeList*,char const*,size_t,size_t) ; 
 struct ServiceProbeMatch* parse_match (struct NmapServiceProbeList*,char const*,size_t,size_t) ; 
 void* parse_number (struct NmapServiceProbeList*,char const*,size_t,size_t) ; 
 struct RangeList parse_ports (struct NmapServiceProbeList*,char const*,size_t,size_t) ; 
 int /*<<< orphan*/  parse_probe (struct NmapServiceProbeList*,char const*,size_t,size_t) ; 
 int parse_type (char const*,size_t*,size_t) ; 
 int /*<<< orphan*/  rangelist_merge (int /*<<< orphan*/ *,struct RangeList*) ; 
 int /*<<< orphan*/  rangelist_remove_all (struct RangeList*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
parse_line(struct NmapServiceProbeList *list, const char *line)
{
    const char *filename = list->filename;
    unsigned line_number = list->line_number;
    size_t line_length;
    size_t offset;
    enum SvcP_RecordType type;
    struct RangeList ranges = {0};
    struct NmapServiceProbe *probe;
    
    
    /* trim whitespace */
    offset = 0;
    line_length = strlen(line);
    while (offset && isspace(line[offset]))
        offset++;
    while (line_length && isspace(line[line_length-1]))
        line_length--;
    
    /* Ignore comment lines */
    if (ispunct(line[offset]))
        return;
    
    /* Ignore empty lines */
    if (offset >= line_length)
        return;
    
    /* parse the type field field */
    type = parse_type(line, &offset, line_length);
    
    /* parse the remainder of the line, depending upon the type */
    switch ((int)type) {
        case SvcP_Unknown:
            fprintf(stderr, "%s:%u:%u: unknown type: '%.*s'\n", filename, line_number, (unsigned)offset, (int)offset-0, line);
            return;
        case SvcP_Exclude:
            if (list->count) {
                /* The 'Exclude' directive is only valid at the top of the file,
                 * before any Probes */
                fprintf(stderr, "%s:%u:%u: 'Exclude' directive only valid before any 'Probe'\n", filename, line_number, (unsigned)offset);
            } else {
                ranges = parse_ports(list, line, offset, line_length);
                if (ranges.count == 0) {
                    fprintf(stderr, "%s:%u:%u: 'Exclude' bad format\n", filename, line_number, (unsigned)offset);
                } else {
                    rangelist_merge(&list->exclude, &ranges);
                    rangelist_remove_all(&ranges);
                }
            }
            return;
        case SvcP_Probe:
            /* Creates a new probe record, all the other types (except 'Exclude') operate
             * on the current probe reocrd */
            parse_probe(list, line, offset, line_length);
            return;
    }
    
    /*
     * The remaining items only work in the context of the current 'Probe'
     * directive
     */
    if (list->count == 0) {
        fprintf(stderr, "%s:%u:%u: 'directive only valid after a 'Probe'\n", filename, line_number, (unsigned)offset);
        return;
    }
    probe = list->list[list->count-1];
    
    switch ((int)type) {
        case SvcP_Ports:
            ranges = parse_ports(list, line, offset, line_length);
            if (ranges.count == 0) {
                fprintf(stderr, "%s:%u:%u: bad ports format\n", filename, line_number, (unsigned)offset);
            } else {
                rangelist_merge(&probe->ports, &ranges);
                rangelist_remove_all(&ranges);
            }
            break;
        case SvcP_Sslports:
            ranges = parse_ports(list, line, offset, line_length);
            if (ranges.count == 0) {
                fprintf(stderr, "%s:%u:%u: bad ports format\n", filename, line_number, (unsigned)offset);
            } else {
                rangelist_merge(&probe->sslports, &ranges);
                rangelist_remove_all(&ranges);
            }
            break;
        case SvcP_Match:
        case SvcP_Softmatch:
            {
                struct ServiceProbeMatch *match;
            
                match = parse_match(list, line, offset, line_length);
                if (match) {
                    struct ServiceProbeMatch **r_match;
                    
                    /* put at end of list */
                    for (r_match = &probe->match; *r_match; r_match = &(*r_match)->next)
                        ;
                    match->next = *r_match;
                    *r_match = match;
                    match->is_softmatch = (type == SvcP_Softmatch);
                }
            }
            break;
        
        case SvcP_Totalwaitms:
            probe->totalwaitms = parse_number(list, line, offset, line_length);
            break;
        case SvcP_Tcpwrappedms:
            probe->tcpwrappedms = parse_number(list, line, offset, line_length);
            break;
        case SvcP_Rarity:
            probe->rarity = parse_number(list, line, offset, line_length);
            break;
        case SvcP_Fallback:
        {
            struct ServiceProbeFallback *fallback;
            fallback = parse_fallback(list, line, offset, line_length);
            if (fallback) {
                fallback->next = probe->fallback;
                probe->fallback = fallback;
            }
        }
            break;
    }

}