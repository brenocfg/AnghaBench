#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rsi {TYPE_2__ in_token; TYPE_1__ in_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSI_HASHBITS ; 
 int hash_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rsi_hash(struct rsi *item)
{
	return hash_mem(item->in_handle.data, item->in_handle.len, RSI_HASHBITS)
	     ^ hash_mem(item->in_token.data, item->in_token.len, RSI_HASHBITS);
}