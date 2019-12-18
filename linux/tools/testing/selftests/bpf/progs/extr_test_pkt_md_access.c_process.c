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
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int TC_ACT_OK ; 
 int /*<<< orphan*/  TEST_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __u16 ; 
 int /*<<< orphan*/  __u32 ; 
 int /*<<< orphan*/  __u8 ; 
 int /*<<< orphan*/  hash ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  protocol ; 

int process(struct __sk_buff *skb)
{
	TEST_FIELD(__u8,  len, 0xFF);
	TEST_FIELD(__u16, len, 0xFFFF);
	TEST_FIELD(__u32, len, 0xFFFFFFFF);
	TEST_FIELD(__u16, protocol, 0xFFFF);
	TEST_FIELD(__u32, protocol, 0xFFFFFFFF);
	TEST_FIELD(__u8,  hash, 0xFF);
	TEST_FIELD(__u16, hash, 0xFFFF);
	TEST_FIELD(__u32, hash, 0xFFFFFFFF);

	return TC_ACT_OK;
}