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
struct m_sub_property {char* member_0; int /*<<< orphan*/  member_1; } ;
struct m_property {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_ASS_0 ; 
 int /*<<< orphan*/  OSD_ASS_1 ; 
 int /*<<< orphan*/  SUB_PROP_STR (int /*<<< orphan*/ ) ; 
 int m_property_read_sub (struct m_sub_property*,int,void*) ; 

__attribute__((used)) static int mp_property_osd_ass(void *ctx, struct m_property *prop,
                               int action, void *arg)
{
    struct m_sub_property props[] = {
        {"0",   SUB_PROP_STR(OSD_ASS_0)},
        {"1",   SUB_PROP_STR(OSD_ASS_1)},
        {0}
    };
    return m_property_read_sub(props, action, arg);
}