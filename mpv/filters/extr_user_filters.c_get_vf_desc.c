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
struct m_obj_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int get_desc_from (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct m_obj_desc*,int) ; 
 int /*<<< orphan*/  vf_list ; 

__attribute__((used)) static bool get_vf_desc(struct m_obj_desc *dst, int index)
{
    return get_desc_from(vf_list, MP_ARRAY_SIZE(vf_list), dst, index);
}