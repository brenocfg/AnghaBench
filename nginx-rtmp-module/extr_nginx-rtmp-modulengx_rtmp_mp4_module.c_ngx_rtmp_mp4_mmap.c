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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  ngx_fd_t ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
ngx_rtmp_mp4_mmap(ngx_fd_t fd, size_t size, off_t offset, ngx_fd_t *extra)
{
    void  *data;

    data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, offset);

    /* valid address is never NULL since there's no MAP_FIXED */

    return data == MAP_FAILED ? NULL : data;
}