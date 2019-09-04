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
typedef  enum extstore_res { ____Placeholder_extstore_res } extstore_res ;

/* Variables and functions */
#define  EXTSTORE_INIT_BAD_WBUF_SIZE 135 
#define  EXTSTORE_INIT_NEED_MORE_BUCKETS 134 
#define  EXTSTORE_INIT_NEED_MORE_WBUF 133 
#define  EXTSTORE_INIT_OOM 132 
#define  EXTSTORE_INIT_OPEN_FAIL 131 
#define  EXTSTORE_INIT_PAGE_WBUF_ALIGNMENT 130 
#define  EXTSTORE_INIT_THREAD_FAIL 129 
#define  EXTSTORE_INIT_TOO_MANY_PAGES 128 

const char *extstore_err(enum extstore_res res) {
    char *rv = "unknown error";
    switch (res) {
        case EXTSTORE_INIT_BAD_WBUF_SIZE:
            rv = "page_size must be divisible by wbuf_size";
            break;
        case EXTSTORE_INIT_NEED_MORE_WBUF:
            rv = "wbuf_count must be >= page_buckets";
            break;
        case EXTSTORE_INIT_NEED_MORE_BUCKETS:
            rv = "page_buckets must be > 0";
            break;
        case EXTSTORE_INIT_PAGE_WBUF_ALIGNMENT:
            rv = "page_size and wbuf_size must be divisible by 1024*1024*2";
            break;
        case EXTSTORE_INIT_TOO_MANY_PAGES:
            rv = "page_count must total to < 65536. Increase page_size or lower path sizes";
            break;
        case EXTSTORE_INIT_OOM:
            rv = "failed calloc for engine";
            break;
        case EXTSTORE_INIT_OPEN_FAIL:
            rv = "failed to open file";
            break;
        case EXTSTORE_INIT_THREAD_FAIL:
            break;
    }
    return rv;
}