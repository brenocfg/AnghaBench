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

/* Variables and functions */
 scalar_t__ isinf (scalar_t__) ; 
 scalar_t__ isnan (scalar_t__) ; 

__attribute__((used)) static inline int is_true(calculated_number n) {
    if(isnan(n)) return 0;
    if(isinf(n)) return 1;
    if(n == 0) return 0;
    return 1;
}