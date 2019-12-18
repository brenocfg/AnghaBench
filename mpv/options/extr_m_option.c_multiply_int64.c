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
typedef  int /*<<< orphan*/  m_option_t ;
typedef  double int64_t ;

/* Variables and functions */
 double INT64_MAX ; 
 double INT64_MIN ; 
 int /*<<< orphan*/  clamp_int64 (int /*<<< orphan*/  const*,void*) ; 

__attribute__((used)) static void multiply_int64(const m_option_t *opt, void *val, double f)
{
    double v = *(int64_t *)val * f;
    int64_t iv = v;
    if (v < INT64_MIN)
        iv = INT64_MIN;
    if (v > INT64_MAX)
        iv = INT64_MAX;
    *(int64_t *)val = iv;
    clamp_int64(opt, val);
}