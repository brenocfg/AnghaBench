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
typedef  int /*<<< orphan*/  APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MTA ; 
 int /*<<< orphan*/  apartment_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csApartment ; 

__attribute__((used)) static APARTMENT *apartment_find_mta(void)
{
    APARTMENT *apt;

    EnterCriticalSection(&csApartment);

    if ((apt = MTA))
        apartment_addref(apt);

    LeaveCriticalSection(&csApartment);

    return apt;
}