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
typedef  int /*<<< orphan*/  RRD_MEMORY_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  RRD_MEMORY_MODE_ALLOC ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_ALLOC_NAME ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_DBENGINE ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_DBENGINE_NAME ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_MAP ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_MAP_NAME ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_NONE ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_NONE_NAME ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_RAM ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_RAM_NAME ; 
 int /*<<< orphan*/  RRD_MEMORY_MODE_SAVE ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

RRD_MEMORY_MODE rrd_memory_mode_id(const char *name) {
    if(unlikely(!strcmp(name, RRD_MEMORY_MODE_RAM_NAME)))
        return RRD_MEMORY_MODE_RAM;

    else if(unlikely(!strcmp(name, RRD_MEMORY_MODE_MAP_NAME)))
        return RRD_MEMORY_MODE_MAP;

    else if(unlikely(!strcmp(name, RRD_MEMORY_MODE_NONE_NAME)))
        return RRD_MEMORY_MODE_NONE;

    else if(unlikely(!strcmp(name, RRD_MEMORY_MODE_ALLOC_NAME)))
        return RRD_MEMORY_MODE_ALLOC;

    else if(unlikely(!strcmp(name, RRD_MEMORY_MODE_DBENGINE_NAME)))
        return RRD_MEMORY_MODE_DBENGINE;

    return RRD_MEMORY_MODE_SAVE;
}