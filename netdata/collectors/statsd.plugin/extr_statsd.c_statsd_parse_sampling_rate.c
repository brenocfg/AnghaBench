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
typedef  double LONG_DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  isgreater (double,double) ; 
 int /*<<< orphan*/  isless (double,double) ; 
 double statsd_parse_float (char const*,double) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LONG_DOUBLE statsd_parse_sampling_rate(const char *v) {
    LONG_DOUBLE sampling_rate = statsd_parse_float(v, 1.0);
    if(unlikely(isless(sampling_rate, 0.001))) sampling_rate = 0.001;
    if(unlikely(isgreater(sampling_rate, 1.0))) sampling_rate = 1.0;
    return sampling_rate;
}