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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct page {int dummy; } ;
struct fscache_cookie {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  __fscache_check_page_write (struct fscache_cookie*,struct page*) ; 
 int /*<<< orphan*/ * bit_waitqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool release_page_wait_timeout(struct fscache_cookie *cookie, struct page *page)
{
	wait_queue_head_t *wq = bit_waitqueue(&cookie->flags, 0);

	return wait_event_timeout(*wq, !__fscache_check_page_write(cookie, page),
				  HZ);
}