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
struct trie {int dummy; } ;
struct key_vector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_TRIE (struct key_vector*) ; 
 struct key_vector* resize (struct trie*,struct key_vector*) ; 

__attribute__((used)) static void trie_rebalance(struct trie *t, struct key_vector *tn)
{
	while (!IS_TRIE(tn))
		tn = resize(t, tn);
}