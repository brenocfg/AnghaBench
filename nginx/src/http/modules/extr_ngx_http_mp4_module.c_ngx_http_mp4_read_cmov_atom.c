#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ name; int /*<<< orphan*/  log; } ;
struct TYPE_7__ {TYPE_2__ file; } ;
typedef  TYPE_3__ ngx_http_mp4_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_read_cmov_atom(ngx_http_mp4_file_t *mp4, uint64_t atom_data_size)
{
    ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                  "\"%s\" mp4 compressed moov atom (cmov) is not supported",
                  mp4->file.name.data);

    return NGX_ERROR;
}