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
struct sk_buff {int dummy; } ;
struct iov_iter {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int __skb_datagram_iter (struct sk_buff const*,int,struct iov_iter*,int,int,int /*<<< orphan*/ ,struct ahash_request*) ; 
 int /*<<< orphan*/  hash_and_copy_to_iter ; 

int skb_copy_and_hash_datagram_iter(const struct sk_buff *skb, int offset,
			   struct iov_iter *to, int len,
			   struct ahash_request *hash)
{
	return __skb_datagram_iter(skb, offset, to, len, true,
			hash_and_copy_to_iter, hash);
}