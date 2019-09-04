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
struct Range6List {int dummy; } ;
struct TYPE_2__ {int hi; int lo; } ;
struct Range6 {TYPE_1__ begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGRESS (int) ; 
 int /*<<< orphan*/  memset (struct Range6List*,int /*<<< orphan*/ ,int) ; 
 struct Range6 range6_parse (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regress_pick2 () ; 

int
ranges6_selftest(void)
{
    struct Range6 r;
    struct Range6List targets[1];

    REGRESS(regress_pick2() == 0);

    memset(targets, 0, sizeof(targets[0]));
#define ERROR() fprintf(stderr, "selftest: failed %s:%u\n", __FILE__, __LINE__);

    /* test for the /0 CIDR block, since we'll be using that a lot to scan the entire
     * Internet */
    r = range6_parse("2001:0db8:85a3:0000:0000:8a2e:0370:7334", 0, 0);
    if (r.begin.hi != 0x20010db885a30000)
        return 1;
    if (r.begin.lo != 0x00008a2e03707334)
        return 1;

    return 0;
}