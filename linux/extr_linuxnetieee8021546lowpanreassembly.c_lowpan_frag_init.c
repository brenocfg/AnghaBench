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
struct inet_frag_queue {int /*<<< orphan*/  key; } ;
struct frag_lowpan_compare_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct frag_lowpan_compare_key const*,int) ; 

__attribute__((used)) static void lowpan_frag_init(struct inet_frag_queue *q, const void *a)
{
	const struct frag_lowpan_compare_key *key = a;

	BUILD_BUG_ON(sizeof(*key) > sizeof(q->key));
	memcpy(&q->key, key, sizeof(*key));
}