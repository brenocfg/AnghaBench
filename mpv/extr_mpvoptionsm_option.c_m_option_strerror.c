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
#define  M_OPT_DISALLOW_PARAM 132 
#define  M_OPT_INVALID 131 
#define  M_OPT_MISSING_PARAM 130 
#define  M_OPT_OUT_OF_RANGE 129 
#define  M_OPT_UNKNOWN 128 

char *m_option_strerror(int code)
{
    switch (code) {
    case M_OPT_UNKNOWN:
        return "option not found";
    case M_OPT_MISSING_PARAM:
        return "option requires parameter";
    case M_OPT_INVALID:
        return "option parameter could not be parsed";
    case M_OPT_OUT_OF_RANGE:
        return "parameter is outside values allowed for option";
    case M_OPT_DISALLOW_PARAM:
        return "option doesn't take a parameter";
    default:
        return "parser error";
    }
}