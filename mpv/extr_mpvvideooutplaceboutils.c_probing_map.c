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
typedef  enum pl_log_level { ____Placeholder_pl_log_level } pl_log_level ;

/* Variables and functions */
#define  PL_LOG_ERR 130 
#define  PL_LOG_FATAL 129 
 int const PL_LOG_INFO ; 
#define  PL_LOG_WARN 128 

__attribute__((used)) static const enum pl_log_level probing_map(enum pl_log_level level)
{
    switch (level) {
    case PL_LOG_FATAL:
        return PL_LOG_ERR;

    case PL_LOG_ERR:
    case PL_LOG_WARN:
        return PL_LOG_INFO;

    default:
        return level;
    }
}