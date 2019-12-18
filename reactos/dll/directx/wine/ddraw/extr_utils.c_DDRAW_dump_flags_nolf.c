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
struct flag_info {int val; int /*<<< orphan*/  name; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DDRAW_dump_flags_nolf(DWORD flags, const struct flag_info *names, size_t num_names)
{
    unsigned int i;

    for (i=0; i < num_names; i++)
        if ((flags & names[i].val) ||      /* standard flag value */
            ((!flags) && (!names[i].val))) /* zero value only */
            TRACE("%s ", names[i].name);
}