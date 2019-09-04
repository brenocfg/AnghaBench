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
typedef  enum parse_status { ____Placeholder_parse_status } parse_status ;

/* Variables and functions */
 int PARSE_ERR ; 
 int PARSE_SUCCESS ; 
 int PARSE_WARN ; 

__attribute__((used)) static inline void set_parse_status(enum parse_status *current, enum parse_status update)
{
    if (update == PARSE_ERR)
        *current = PARSE_ERR;
    else if (update == PARSE_WARN && *current == PARSE_SUCCESS)
        *current = PARSE_WARN;
}