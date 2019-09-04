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
typedef  int /*<<< orphan*/  const_DES_cblock ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int NUM_WEAK_KEY ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * weak_keys ; 

int DES_is_weak_key(const_DES_cblock *key)
{
    int i;

    for (i = 0; i < NUM_WEAK_KEY; i++)
        if (memcmp(weak_keys[i], key, sizeof(DES_cblock)) == 0)
            return 1;
    return 0;
}