#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_align_ptr (void*,scalar_t__) ; 
 void* ngx_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_cacheline_size ; 
 int /*<<< orphan*/  ngx_crc32_table16 ; 
 void* ngx_crc32_table_short ; 
 TYPE_1__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_memcpy (void*,int /*<<< orphan*/ ,int) ; 

ngx_int_t
ngx_crc32_table_init(void)
{
    void  *p;

    if (((uintptr_t) ngx_crc32_table_short
          & ~((uintptr_t) ngx_cacheline_size - 1))
        == (uintptr_t) ngx_crc32_table_short)
    {
        return NGX_OK;
    }

    p = ngx_alloc(16 * sizeof(uint32_t) + ngx_cacheline_size, ngx_cycle->log);
    if (p == NULL) {
        return NGX_ERROR;
    }

    p = ngx_align_ptr(p, ngx_cacheline_size);

    ngx_memcpy(p, ngx_crc32_table16, 16 * sizeof(uint32_t));

    ngx_crc32_table_short = p;

    return NGX_OK;
}