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
struct dst_entry {int dummy; } ;

/* Variables and functions */
 unsigned int dst_metric_advmss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_dst_path (struct dst_entry const*) ; 

__attribute__((used)) static unsigned int xfrm_default_advmss(const struct dst_entry *dst)
{
	return dst_metric_advmss(xfrm_dst_path(dst));
}