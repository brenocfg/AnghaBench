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
typedef  int /*<<< orphan*/  PROP_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  lh_PROPERTY_STRING_doall (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_PROPERTY_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  property_free ; 

__attribute__((used)) static void property_table_free(PROP_TABLE **pt)
{
    PROP_TABLE *t = *pt;

    if (t != NULL) {
        lh_PROPERTY_STRING_doall(t, &property_free);
        lh_PROPERTY_STRING_free(t);
        *pt = NULL;
    }
}