#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int total_number ;
typedef  int time_t ;
typedef  int collected_number ;
typedef  int calculated_number ;
struct TYPE_3__ {int type; scalar_t__ value; } ;
typedef  TYPE_1__ RRDVAR ;

/* Variables and functions */
 int NAN ; 
#define  RRDVAR_TYPE_CALCULATED 132 
#define  RRDVAR_TYPE_COLLECTED 131 
#define  RRDVAR_TYPE_INT 130 
#define  RRDVAR_TYPE_TIME_T 129 
#define  RRDVAR_TYPE_TOTAL 128 
 int /*<<< orphan*/  error (char*,int) ; 

calculated_number rrdvar2number(RRDVAR *rv) {
    switch(rv->type) {
        case RRDVAR_TYPE_CALCULATED: {
            calculated_number *n = (calculated_number *)rv->value;
            return *n;
        }

        case RRDVAR_TYPE_TIME_T: {
            time_t *n = (time_t *)rv->value;
            return *n;
        }

        case RRDVAR_TYPE_COLLECTED: {
            collected_number *n = (collected_number *)rv->value;
            return *n;
        }

        case RRDVAR_TYPE_TOTAL: {
            total_number *n = (total_number *)rv->value;
            return *n;
        }

        case RRDVAR_TYPE_INT: {
            int *n = (int *)rv->value;
            return *n;
        }

        default:
            error("I don't know how to convert RRDVAR type %u to calculated_number", rv->type);
            return NAN;
    }
}