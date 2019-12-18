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
typedef  int /*<<< orphan*/  xx ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t SMACK_NOT_FOUND ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  global_mib ; 
 TYPE_1__* mib ; 
 size_t smack_search_next (int /*<<< orphan*/ ,unsigned int*,unsigned char const*,unsigned int*,unsigned int) ; 
 scalar_t__ snmp_selftest_banner () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
snmp_selftest(void)
{
    static const unsigned char xx[] = {
        43, 0x80|7, 110, 51, 0x80|20, 0x80|106, 84,
    };
    size_t i;
    unsigned state;
    unsigned offset;
    size_t found_id = SMACK_NOT_FOUND;


    if (snmp_selftest_banner())
        return 1;

    /*
     * test of searching OIDs
     */
    state = 0;
    offset = 0;
    while (offset < sizeof(xx)) {
        i = smack_search_next(  global_mib,
                                &state,
                                xx,
                                &offset,
                                (unsigned)sizeof(xx)
                                );
        if (i != SMACK_NOT_FOUND)
            found_id = i;
    }
    if (found_id == SMACK_NOT_FOUND) {
        fprintf(stderr, "snmp: oid parser failed\n");
        return 1;
    }
    if (strcmp(mib[found_id].name, "selftest") != 0) {
        fprintf(stderr, "snmp: oid parser failed\n");
        return 1;
    }



    return 0;
}