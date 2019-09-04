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
struct RangeList {int /*<<< orphan*/  member_0; } ;
struct PayloadsUDP {int dummy; } ;
struct TYPE_2__ {int length; int /*<<< orphan*/  set_cookie; int /*<<< orphan*/  source_port; scalar_t__ buf; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 struct PayloadsUDP* CALLOC (int,int) ; 
 TYPE_1__* hard_coded_payloads ; 
 int /*<<< orphan*/  payloads_udp_add (struct PayloadsUDP*,unsigned char const*,unsigned int,struct RangeList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_add_range (struct RangeList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_remove_all (struct RangeList*) ; 
 scalar_t__ strlen (scalar_t__) ; 

struct PayloadsUDP *
payloads_udp_create(void)
{
    unsigned i;
    struct PayloadsUDP *payloads;
    
    payloads = CALLOC(1, sizeof(*payloads));
    
    /*
     * For popular parts, include some hard-coded default UDP payloads
     */
    for (i=0; hard_coded_payloads[i].length; i++) {
        //struct Range range;
        struct RangeList list = {0};
        unsigned length;

        /* Kludge: create a pseudo-rangelist to hold the one port */
        /*list.list = &range;
        list.count = 1;
        range.begin = hard_coded_payloads[i].port;
        range.end = range.begin;*/
        rangelist_add_range(&list, hard_coded_payloads[i].port, hard_coded_payloads[i].port);

        length = hard_coded_payloads[i].length;
        if (length == 0xFFFFFFFF)
            length = (unsigned)strlen(hard_coded_payloads[i].buf);

        /* Add this to our real payloads. This will get overwritten
         * if the user adds their own with the same port */
        payloads_udp_add(payloads,
                    (const unsigned char*)hard_coded_payloads[i].buf,
                    length,
                    &list,
                    hard_coded_payloads[i].source_port,
                    hard_coded_payloads[i].set_cookie);

        rangelist_remove_all(&list);
    }
    return payloads;
}