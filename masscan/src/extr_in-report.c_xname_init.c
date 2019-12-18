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
struct TYPE_2__ {char* name; unsigned int length; unsigned int code; } ;

/* Variables and functions */
 int /*<<< orphan*/  global_xnames ; 
 TYPE_1__* mynames ; 
 int /*<<< orphan*/  smack_add_pattern (int /*<<< orphan*/ ,char const*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_compile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_create (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xname_init(void)
{
    unsigned i;

    global_xnames = smack_create("readscan-x509-names", 0);

    for (i=0; mynames[i].name; i++) {
        const char *pattern = mynames[i].name;
        unsigned len = mynames[i].length;
        unsigned id = mynames[i].code;


        smack_add_pattern(  global_xnames,
                            pattern,
                            len,
                            id,
                            0
                            );
    }

    smack_compile(global_xnames);

}