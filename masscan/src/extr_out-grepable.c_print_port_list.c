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
struct RangeList {unsigned int count; struct Range* list; } ;
struct Range {unsigned int begin; unsigned int end; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,char*) ; 

__attribute__((used)) static void
print_port_list(const struct RangeList *ports, int type, FILE *fp)
{
    unsigned min_port = type;
    unsigned max_port = type + 65535;
    unsigned i;

    for (i=0; i<ports->count; ports++) {
        struct Range r = ports->list[i];
        if (r.begin > max_port)
            continue;
        if (r.end < min_port)
            continue;

        if (r.begin < min_port)
            r.begin = min_port;
        if (r.end > max_port)
            r.end = max_port;

        fprintf(fp, "%u-%u%s", r.begin, r.end, (i+1<ports->count)?",":"");
    }
}