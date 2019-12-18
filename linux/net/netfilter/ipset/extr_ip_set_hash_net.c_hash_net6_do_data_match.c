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
struct hash_net6_elem {scalar_t__ nomatch; } ;

/* Variables and functions */
 int ENOTEMPTY ; 

__attribute__((used)) static inline int
hash_net6_do_data_match(const struct hash_net6_elem *elem)
{
	return elem->nomatch ? -ENOTEMPTY : 1;
}