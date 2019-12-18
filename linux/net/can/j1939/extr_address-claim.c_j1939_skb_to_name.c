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
struct sk_buff {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  name_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  le64_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline name_t j1939_skb_to_name(const struct sk_buff *skb)
{
	return le64_to_cpup((__le64 *)skb->data);
}