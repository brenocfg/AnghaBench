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

/* Variables and functions */
 int /*<<< orphan*/  purge_user_pass (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  static_proxy_user_pass ; 

__attribute__((used)) static void
clear_user_pass_http(void)
{
    purge_user_pass(&static_proxy_user_pass, true);
}