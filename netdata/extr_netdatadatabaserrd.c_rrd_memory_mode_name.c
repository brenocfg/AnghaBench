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
typedef  int RRD_MEMORY_MODE ;

/* Variables and functions */
#define  RRD_MEMORY_MODE_ALLOC 132 
 char const* RRD_MEMORY_MODE_ALLOC_NAME ; 
#define  RRD_MEMORY_MODE_MAP 131 
 char const* RRD_MEMORY_MODE_MAP_NAME ; 
#define  RRD_MEMORY_MODE_NONE 130 
 char const* RRD_MEMORY_MODE_NONE_NAME ; 
#define  RRD_MEMORY_MODE_RAM 129 
 char const* RRD_MEMORY_MODE_RAM_NAME ; 
#define  RRD_MEMORY_MODE_SAVE 128 
 char const* RRD_MEMORY_MODE_SAVE_NAME ; 

inline const char *rrd_memory_mode_name(RRD_MEMORY_MODE id) {
    switch(id) {
        case RRD_MEMORY_MODE_RAM:
            return RRD_MEMORY_MODE_RAM_NAME;

        case RRD_MEMORY_MODE_MAP:
            return RRD_MEMORY_MODE_MAP_NAME;

        case RRD_MEMORY_MODE_NONE:
            return RRD_MEMORY_MODE_NONE_NAME;

        case RRD_MEMORY_MODE_SAVE:
            return RRD_MEMORY_MODE_SAVE_NAME;

        case RRD_MEMORY_MODE_ALLOC:
            return RRD_MEMORY_MODE_ALLOC_NAME;
    }

    return RRD_MEMORY_MODE_SAVE_NAME;
}