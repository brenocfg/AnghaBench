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
typedef  int /*<<< orphan*/  RRDSET_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA_NAME ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED_NAME ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

inline RRDSET_TYPE rrdset_type_id(const char *name) {
    if(unlikely(strcmp(name, RRDSET_TYPE_AREA_NAME) == 0))
        return RRDSET_TYPE_AREA;

    else if(unlikely(strcmp(name, RRDSET_TYPE_STACKED_NAME) == 0))
        return RRDSET_TYPE_STACKED;

    else // if(unlikely(strcmp(name, RRDSET_TYPE_LINE_NAME) == 0))
        return RRDSET_TYPE_LINE;
}