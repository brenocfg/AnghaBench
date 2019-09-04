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
struct m_property_action_arg {scalar_t__ arg; int /*<<< orphan*/  action; int /*<<< orphan*/  key; } ;
struct m_option {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_TYPE_TIME ; 
 double MP_NOPTS_VALUE ; 
#define  M_PROPERTY_GET 131 
#define  M_PROPERTY_GET_TYPE 130 
#define  M_PROPERTY_KEY_ACTION 129 
 int M_PROPERTY_NOT_IMPLEMENTED ; 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 128 
 int M_PROPERTY_UNAVAILABLE ; 
 int M_PROPERTY_UNKNOWN ; 
 char* mp_format_time (double,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int property_time(int action, void *arg, double time)
{
    if (time == MP_NOPTS_VALUE)
        return M_PROPERTY_UNAVAILABLE;

    const struct m_option time_type = {.type = CONF_TYPE_TIME};
    switch (action) {
    case M_PROPERTY_GET:
        *(double *)arg = time;
        return M_PROPERTY_OK;
    case M_PROPERTY_GET_TYPE:
        *(struct m_option *)arg = time_type;
        return M_PROPERTY_OK;
    case M_PROPERTY_KEY_ACTION: {
        struct m_property_action_arg *ka = arg;

        if (strcmp(ka->key, "full") != 0)
            return M_PROPERTY_UNKNOWN;

        switch (ka->action) {
        case M_PROPERTY_GET:
            *(double *)ka->arg = time;
            return M_PROPERTY_OK;
        case M_PROPERTY_PRINT:
            *(char **)ka->arg = mp_format_time(time, true);
            return M_PROPERTY_OK;
        case M_PROPERTY_GET_TYPE:
            *(struct m_option *)ka->arg = time_type;
            return M_PROPERTY_OK;
        }
    }
    }
    return M_PROPERTY_NOT_IMPLEMENTED;
}