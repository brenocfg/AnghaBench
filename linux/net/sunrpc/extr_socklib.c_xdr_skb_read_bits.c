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
struct xdr_skb_reader {size_t count; size_t offset; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_copy_bits (int /*<<< orphan*/ ,size_t,void*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
xdr_skb_read_bits(struct xdr_skb_reader *desc, void *to, size_t len)
{
	if (len > desc->count)
		len = desc->count;
	if (unlikely(skb_copy_bits(desc->skb, desc->offset, to, len)))
		return 0;
	desc->count -= len;
	desc->offset += len;
	return len;
}