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
typedef  int /*<<< orphan*/  pattern ;
struct TYPE_2__ {int /*<<< orphan*/  oid; scalar_t__ name; } ;

/* Variables and functions */
 int SMACK_ANCHOR_BEGIN ; 
 int SMACK_SNMP_HACK ; 
 unsigned int convert_oid (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_mib ; 
 TYPE_1__* mib ; 
 int /*<<< orphan*/  smack_add_pattern (int /*<<< orphan*/ ,unsigned char*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  smack_compile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_create (char*,int /*<<< orphan*/ ) ; 

void
x509_init(void)
{
    unsigned i;

    /* We use an Aho-Corasick pattern matcher for this. Not necessarily
     * the most efficient, but also not bad */
    global_mib = smack_create("ssl-oids", 0);

    /* We just go through the table of OIDs and add them all one by
     * one */
    for (i=0; mib[i].name; i++) {
        unsigned char pattern[256];
        unsigned len;

        len = convert_oid(pattern, sizeof(pattern), mib[i].oid);

        smack_add_pattern(  global_mib,
                            pattern,
                            len,
                            i,
                            SMACK_ANCHOR_BEGIN | SMACK_SNMP_HACK
                            );
    }

    /* Now that we've added all the OIDs, we need to compile this into
     * an efficientdata structure. Later, when we get packets, we'll
     * use this for searching */
    smack_compile(global_mib);

}