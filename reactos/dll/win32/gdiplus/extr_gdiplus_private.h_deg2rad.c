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
typedef  double REAL ;

/* Variables and functions */
 double M_PI ; 

__attribute__((used)) static inline REAL deg2rad(REAL degrees)
{
    return M_PI * degrees / 180.0;
}