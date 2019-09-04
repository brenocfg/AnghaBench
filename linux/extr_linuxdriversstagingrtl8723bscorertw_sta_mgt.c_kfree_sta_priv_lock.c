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
struct sta_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_all_stainfo (struct sta_priv*) ; 

void kfree_sta_priv_lock(struct	sta_priv *pstapriv)
{
	 kfree_all_stainfo(pstapriv); /* be done before free sta_hash_lock */
}