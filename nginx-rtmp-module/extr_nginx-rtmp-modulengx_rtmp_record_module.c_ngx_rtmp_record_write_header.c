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
typedef  int u_char ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_file_t ;
typedef  int /*<<< orphan*/  flv_header ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_write_file (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_record_write_header(ngx_file_t *file)
{
    static u_char       flv_header[] = {
        0x46, /* 'F' */
        0x4c, /* 'L' */
        0x56, /* 'V' */
        0x01, /* version = 1 */
        0x05, /* 00000 1 0 1 = has audio & video */
        0x00,
        0x00,
        0x00,
        0x09, /* header size */
        0x00,
        0x00,
        0x00,
        0x00  /* PreviousTagSize0 (not actually a header) */
    };

    return ngx_write_file(file, flv_header, sizeof(flv_header), 0) == NGX_ERROR
           ? NGX_ERROR
           : NGX_OK;
}