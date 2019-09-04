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
typedef  int __u64 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int load_word (struct __sk_buff*,int) ; 

__attribute__((used)) static inline __u32 ipv6_addr_hash(struct __sk_buff *ctx, __u64 off)
{
	__u64 w0 = load_word(ctx, off);
	__u64 w1 = load_word(ctx, off + 4);
	__u64 w2 = load_word(ctx, off + 8);
	__u64 w3 = load_word(ctx, off + 12);

	return (__u32)(w0 ^ w1 ^ w2 ^ w3);
}