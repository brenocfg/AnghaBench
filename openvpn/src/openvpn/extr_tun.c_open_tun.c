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
struct tuntap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  open_tun_generic (char const*,char const*,char const*,int,struct tuntap*) ; 

void
open_tun(const char *dev, const char *dev_type, const char *dev_node, struct tuntap *tt)
{
    open_tun_generic(dev, dev_type, dev_node, true, tt);
}