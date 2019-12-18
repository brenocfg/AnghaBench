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
struct m_option {int /*<<< orphan*/  type; } ;
typedef  size_t mpv_format ;

/* Variables and functions */
 unsigned int MP_ARRAY_SIZE (struct m_option const*) ; 
 struct m_option const* type_conv ; 

__attribute__((used)) static const struct m_option *get_mp_type(mpv_format format)
{
    if ((unsigned)format >= MP_ARRAY_SIZE(type_conv))
        return NULL;
    if (!type_conv[format].type)
        return NULL;
    return &type_conv[format];
}