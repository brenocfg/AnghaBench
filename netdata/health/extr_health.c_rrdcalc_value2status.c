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
typedef  scalar_t__ calculated_number ;
typedef  int /*<<< orphan*/  RRDCALC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RRDCALC_STATUS_CLEAR ; 
 int /*<<< orphan*/  RRDCALC_STATUS_RAISED ; 
 int /*<<< orphan*/  RRDCALC_STATUS_UNDEFINED ; 
 scalar_t__ isinf (scalar_t__) ; 
 scalar_t__ isnan (scalar_t__) ; 

__attribute__((used)) static inline RRDCALC_STATUS rrdcalc_value2status(calculated_number n) {
    if(isnan(n) || isinf(n)) return RRDCALC_STATUS_UNDEFINED;
    if(n) return RRDCALC_STATUS_RAISED;
    return RRDCALC_STATUS_CLEAR;
}