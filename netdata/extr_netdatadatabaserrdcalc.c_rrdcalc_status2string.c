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
typedef  int RRDCALC_STATUS ;

/* Variables and functions */
#define  RRDCALC_STATUS_CLEAR 134 
#define  RRDCALC_STATUS_CRITICAL 133 
#define  RRDCALC_STATUS_RAISED 132 
#define  RRDCALC_STATUS_REMOVED 131 
#define  RRDCALC_STATUS_UNDEFINED 130 
#define  RRDCALC_STATUS_UNINITIALIZED 129 
#define  RRDCALC_STATUS_WARNING 128 
 int /*<<< orphan*/  error (char*,int) ; 

inline const char *rrdcalc_status2string(RRDCALC_STATUS status) {
    switch(status) {
        case RRDCALC_STATUS_REMOVED:
            return "REMOVED";

        case RRDCALC_STATUS_UNDEFINED:
            return "UNDEFINED";

        case RRDCALC_STATUS_UNINITIALIZED:
            return "UNINITIALIZED";

        case RRDCALC_STATUS_CLEAR:
            return "CLEAR";

        case RRDCALC_STATUS_RAISED:
            return "RAISED";

        case RRDCALC_STATUS_WARNING:
            return "WARNING";

        case RRDCALC_STATUS_CRITICAL:
            return "CRITICAL";

        default:
            error("Unknown alarm status %d", status);
            return "UNKNOWN";
    }
}