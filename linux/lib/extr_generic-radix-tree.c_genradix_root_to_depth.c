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
struct genradix_root {int dummy; } ;

/* Variables and functions */
 unsigned long GENRADIX_DEPTH_MASK ; 

__attribute__((used)) static inline unsigned genradix_root_to_depth(struct genradix_root *r)
{
	return (unsigned long) r & GENRADIX_DEPTH_MASK;
}