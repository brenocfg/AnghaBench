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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  LPCTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  MOVEFILE_REPLACE_EXISTING ; 
 int /*<<< orphan*/  MoveFileEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rename_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_hls_rename_file(u_char *src, u_char *dst)
{
    /* rename file with overwrite */

#if (NGX_WIN32)
    return MoveFileEx((LPCTSTR) src, (LPCTSTR) dst, MOVEFILE_REPLACE_EXISTING);
#else
    return ngx_rename_file(src, dst);
#endif
}