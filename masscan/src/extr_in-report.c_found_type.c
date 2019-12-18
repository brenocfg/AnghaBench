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

/* Variables and functions */
 size_t SMACK_NOT_FOUND ; 
 int /*<<< orphan*/ * counts ; 
 int /*<<< orphan*/  global_xnames ; 
 size_t smack_search_next (int /*<<< orphan*/ ,unsigned int*,unsigned char const*,unsigned int*,unsigned int) ; 

__attribute__((used)) static unsigned
found_type(const unsigned char *banner, size_t banner_length)
{
    size_t id;
    unsigned state = 0;
    unsigned offset = 0;

    /*for (i=0; mynames[i].name; i++) {
        if (found(mynames[i].name, mynames[i].length, banner, banner_length))
            return 1;
    }*/

    id = smack_search_next( global_xnames,
                                        &state,
                                        banner,
                                        &offset,
                                        (unsigned)banner_length);
    if (id == SMACK_NOT_FOUND)
        return 0;
    
    counts[id]++;

    return 1;
}