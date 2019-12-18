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
struct m_option {int /*<<< orphan*/ * type; int /*<<< orphan*/  member_0; } ;
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PROPERTY_GET_TYPE ; 
 int /*<<< orphan*/  m_option_type_aspect ; 
 int /*<<< orphan*/  m_option_type_double ; 
 int /*<<< orphan*/  m_option_type_float ; 
 int /*<<< orphan*/  m_option_type_time ; 
 scalar_t__ mp_property_do (char*,int /*<<< orphan*/ ,struct m_option*,struct MPContext*) ; 

__attribute__((used)) static bool check_property_scalable(char *property, struct MPContext *mpctx)
{
    struct m_option prop = {0};
    if (mp_property_do(property, M_PROPERTY_GET_TYPE, &prop, mpctx) <= 0)
        return true;

    // These properties are backed by a floating-point number
    return prop.type == &m_option_type_float ||
           prop.type == &m_option_type_double ||
           prop.type == &m_option_type_time ||
           prop.type == &m_option_type_aspect;
}