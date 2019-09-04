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
struct zcrypt_card {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_card_release ; 

int zcrypt_card_put(struct zcrypt_card *zc)
{
	return kref_put(&zc->refcount, zcrypt_card_release);
}