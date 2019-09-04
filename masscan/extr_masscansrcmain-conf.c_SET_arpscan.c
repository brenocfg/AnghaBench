#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Range {void* end; void* begin; } ;
struct TYPE_2__ {int arp; } ;
struct Masscan {TYPE_1__ scan_type; int /*<<< orphan*/  ports; scalar_t__ echo; scalar_t__ echo_all; } ;

/* Variables and functions */
 int CONF_OK ; 
 int /*<<< orphan*/  LOG (int,char*) ; 
 void* Templ_ARP ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  masscan_set_parameter (struct Masscan*,char*,char*) ; 
 int /*<<< orphan*/  rangelist_add_range (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  rangelist_sort (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SET_arpscan(struct Masscan *masscan, const char *name, const char *value)
{
    struct Range range;

    UNUSEDPARM(name);
    UNUSEDPARM(value);

    if (masscan->echo) {
        if (masscan->scan_type.arp || masscan->echo_all)
            fprintf(masscan->echo, "arpscan = %s\n", masscan->scan_type.arp?"true":"false");
        return 0;
    }
    range.begin = Templ_ARP;
    range.end = Templ_ARP;
    rangelist_add_range(&masscan->ports, range.begin, range.end);
    rangelist_sort(&masscan->ports);
    masscan_set_parameter(masscan, "router-mac", "ff-ff-ff-ff-ff-ff");
    masscan->scan_type.arp = 1;
    LOG(5, "--arpscan\n");
    return CONF_OK;
}