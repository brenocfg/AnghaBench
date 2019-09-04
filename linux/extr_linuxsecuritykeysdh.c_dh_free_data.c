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
struct dh {int /*<<< orphan*/  g; int /*<<< orphan*/  p; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dh_free_data(struct dh *dh)
{
	kzfree(dh->key);
	kzfree(dh->p);
	kzfree(dh->g);
}