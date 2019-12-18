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
struct security_attributes {int /*<<< orphan*/  sa; } ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_security_attributes_allow_all (struct security_attributes*) ; 

HANDLE
create_event(LPCTSTR name, bool allow_all, bool initial_state, bool manual_reset)
{
    if (allow_all)
    {
        struct security_attributes sa;
        if (!init_security_attributes_allow_all(&sa))
        {
            return NULL;
        }
        return CreateEvent(&sa.sa, (BOOL)manual_reset, (BOOL)initial_state, name);
    }
    else
    {
        return CreateEvent(NULL, (BOOL)manual_reset, (BOOL)initial_state, name);
    }
}