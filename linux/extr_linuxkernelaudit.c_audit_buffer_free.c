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
struct audit_buffer {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_buffer_cache ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct audit_buffer*) ; 

__attribute__((used)) static void audit_buffer_free(struct audit_buffer *ab)
{
	if (!ab)
		return;

	kfree_skb(ab->skb);
	kmem_cache_free(audit_buffer_cache, ab);
}