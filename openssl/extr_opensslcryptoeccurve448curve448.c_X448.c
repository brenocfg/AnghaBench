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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ C448_SUCCESS ; 
 scalar_t__ x448_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int X448(uint8_t out_shared_key[56], const uint8_t private_key[56],
         const uint8_t peer_public_value[56])
{
    return x448_int(out_shared_key, peer_public_value, private_key)
           == C448_SUCCESS;
}