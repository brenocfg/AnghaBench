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
typedef  int /*<<< orphan*/  targets ;
struct RangeList {int count; TYPE_1__* list; int /*<<< orphan*/  member_0; } ;
struct Range {int begin; int end; } ;
struct TYPE_2__ {int begin; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR () ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  REGRESS (int) ; 
 scalar_t__ exclude_selftest () ; 
 int /*<<< orphan*/  memset (struct RangeList*,int /*<<< orphan*/ ,int) ; 
 struct Range range_parse_ipv4 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_add_range2 (struct RangeList*,struct Range) ; 
 int /*<<< orphan*/  rangelist_parse_ports (struct RangeList*,char*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_remove_all (struct RangeList*) ; 
 int /*<<< orphan*/  rangelist_remove_range2 (struct RangeList*,struct Range) ; 
 int /*<<< orphan*/  rangelist_sort (struct RangeList*) ; 
 scalar_t__ regress_pick2 () ; 

int
ranges_selftest(void)
{
    struct Range r;
    struct RangeList targets[1] = {{0}};

    REGRESS(regress_pick2() == 0);

    /* Do a spearate test of the 'exclude' feature */
    if (exclude_selftest())
        return 1;
    
    memset(targets, 0, sizeof(targets[0]));
#define ERROR() LOG(0, "selftest: failed %s:%u\n", __FILE__, __LINE__);

    /* test for the /0 CIDR block, since we'll be using that a lot to scan the entire
     * Internet */
    r = range_parse_ipv4("0.0.0.0/0", 0, 0);
    REGRESS(r.begin == 0 && r.end == 0xFFFFFFFF);

    r = range_parse_ipv4("0.0.0./0", 0, 0);
    REGRESS(r.begin > r.end);

    r = range_parse_ipv4("75.748.86.91", 0, 0);
    REGRESS(r.begin > r.end);

    r = range_parse_ipv4("23.75.345.200", 0, 0);
    REGRESS(r.begin > r.end);

    r = range_parse_ipv4("192.1083.0.1", 0, 0);
    REGRESS(r.begin > r.end);

    r = range_parse_ipv4("192.168.1.3", 0, 0);
    if (r.begin != 0xc0a80103 || r.end != 0xc0a80103) {
        LOG(0, "r.begin = 0x%08x r.end = 0x%08x\n", r.begin, r.end);
        ERROR();
        return 1;
    }

    r = range_parse_ipv4("10.0.0.20-10.0.0.30", 0, 0);
    if (r.begin != 0x0A000000+20 || r.end != 0x0A000000+30) {
        LOG(0,  "r.begin = 0x%08x r.end = 0x%08x\n", r.begin, r.end);
        ERROR();
        return 1;
    }

    r = range_parse_ipv4("10.0.1.2/16", 0, 0);
    if (r.begin != 0x0A000000 || r.end != 0x0A00FFFF) {
        LOG(0, "r.begin = 0x%08x r.end = 0x%08x\n", r.begin, r.end);
        ERROR();
        return 1;
    }


    rangelist_add_range2(targets, range_parse_ipv4("10.0.0.0/24", 0, 0));
    rangelist_add_range2(targets, range_parse_ipv4("10.0.1.10-10.0.1.19", 0, 0));
    rangelist_add_range2(targets, range_parse_ipv4("10.0.1.20-10.0.1.30", 0, 0));
    rangelist_add_range2(targets, range_parse_ipv4("10.0.0.0-10.0.1.12", 0, 0));
    rangelist_sort(targets);

    if (targets->count != 1) {
        LOG(0, "count = %u\n", targets->count);
        ERROR();
        return 1;
    }
    if (targets->list[0].begin != 0x0a000000 || targets->list[0].end != 0x0a000100+30) {
        LOG(0, "r.begin = 0x%08x r.end = 0x%08x\n", targets->list[0].begin, targets->list[0].end);
        ERROR();
        return 1;
    }

    rangelist_remove_all(targets);

    /*
     * Test removal
     */
    memset(targets, 0, sizeof(targets[0]));

    rangelist_add_range2(targets, range_parse_ipv4("10.0.0.0/8", 0, 0));
    rangelist_sort(targets);

    /* These removals shouldn't change anything */
    rangelist_remove_range2(targets, range_parse_ipv4("9.255.255.255", 0, 0));
    rangelist_remove_range2(targets, range_parse_ipv4("11.0.0.0/16", 0, 0));
    rangelist_remove_range2(targets, range_parse_ipv4("192.168.0.0/16", 0, 0));
    rangelist_sort(targets);

    if (targets->count != 1
        || targets->list->begin != 0x0a000000
        || targets->list->end != 0x0aFFFFFF) {
        ERROR();
        return 1;
    }

    /* These removals should remove a bit from the edges */
    rangelist_remove_range2(targets, range_parse_ipv4("1.0.0.0-10.0.0.0", 0, 0));
    rangelist_remove_range2(targets, range_parse_ipv4("10.255.255.255-11.0.0.0", 0, 0));
    rangelist_sort(targets);
    if (targets->count != 1
        || targets->list->begin != 0x0a000001
        || targets->list->end != 0x0aFFFFFE) {
        ERROR();
        return 1;
    }


    /* remove things from the middle */
    rangelist_remove_range2(targets, range_parse_ipv4("10.10.0.0/16", 0, 0));
    rangelist_remove_range2(targets, range_parse_ipv4("10.20.0.0/16", 0, 0));
    rangelist_sort(targets);
    if (targets->count != 3) {
        ERROR();
        return 1;
    }

    rangelist_remove_range2(targets, range_parse_ipv4("10.12.0.0/16", 0, 0));
    rangelist_sort(targets);
    if (targets->count != 4) {
        ERROR();
        return 1;
    }

    rangelist_remove_range2(targets, range_parse_ipv4("10.10.10.10-10.12.12.12", 0, 0));
    rangelist_sort(targets);
    if (targets->count != 3) {
        ERROR();
        return 1;
    }
    rangelist_remove_all(targets);

    /* test ports */
    {
        unsigned is_error = 0;
        memset(targets, 0, sizeof(targets[0]));

        rangelist_parse_ports(targets, "80,1000-2000,1234,4444", &is_error, 0);
        rangelist_sort(targets);
        if (targets->count != 3 || is_error) {
            ERROR();
            return 1;
        }

        if (targets->list[0].begin != 80 || targets->list[0].end != 80 ||
            targets->list[1].begin != 1000 || targets->list[1].end != 2000 ||
            targets->list[2].begin != 4444 || targets->list[2].end != 4444) {
            ERROR();
            return 1;
        }
    }

    return 0;
}