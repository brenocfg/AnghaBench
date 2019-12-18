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
 int fcgi_init () ; 
 int is_fastcgi ; 
 int /*<<< orphan*/  is_initialized ; 

int fcgi_is_fastcgi(void)
{
	if (!is_initialized) {
		return fcgi_init();
	} else {
		return is_fastcgi;
	}
}