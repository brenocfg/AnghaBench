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
typedef  int t_key ;
struct key_vector {int key; } ;

/* Variables and functions */

__attribute__((used)) static inline t_key prefix_mismatch(t_key key, struct key_vector *n)
{
	t_key prefix = n->key;

	return (key ^ prefix) & (prefix | -prefix);
}