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
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  async_dfl_domain ; 
 int /*<<< orphan*/  async_synchronize_cookie_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void async_synchronize_cookie(async_cookie_t cookie)
{
	async_synchronize_cookie_domain(cookie, &async_dfl_domain);
}