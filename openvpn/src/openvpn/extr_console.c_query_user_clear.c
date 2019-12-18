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
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 int QUERY_USER_NUMSLOTS ; 
 int /*<<< orphan*/ * query_user ; 

void
query_user_clear(void)
{
    int i;

    for (i = 0; i < QUERY_USER_NUMSLOTS; i++)
    {
        CLEAR(query_user[i]);
    }
}