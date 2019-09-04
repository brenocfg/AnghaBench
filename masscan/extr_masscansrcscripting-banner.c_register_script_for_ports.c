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
struct RangeList {unsigned int count; struct Range* list; int /*<<< orphan*/  member_0; } ;
struct Range {unsigned int begin; unsigned int end; } ;
struct Banner1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  rangelist_parse_ports (struct RangeList*,char const*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_script_for_port (struct Banner1*,unsigned int) ; 

__attribute__((used)) static void
register_script_for_ports(struct Banner1 *b, const char *value)
{
    struct RangeList ports = {0};
    unsigned is_error = 0;
    unsigned i;
    
    rangelist_parse_ports(&ports, value, &is_error, 0);
    if (is_error) {
        LOG(0, "SCRIPTING: invalid 'setTcpPorts' range: %s\n", value);
        exit(1);
    }

    for (i=0; i<ports.count; i++) {
        struct Range *range = &ports.list[i];
        unsigned j;
        
        for (j=range->begin; j<=range->end; j++) {
            register_script_for_port(b, j);
        }
    }
    
}