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
struct Source {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_my_ip (struct Source const*,unsigned int) ; 
 scalar_t__ is_my_port (struct Source const*,unsigned int) ; 

int is_myself(const struct Source *src, unsigned ip, unsigned port)
{
    return is_my_ip(src, ip) && is_my_port(src, port);
}