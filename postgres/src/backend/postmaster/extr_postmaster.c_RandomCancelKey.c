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
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int pg_strong_random (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
RandomCancelKey(int32 *cancel_key)
{
	return pg_strong_random(cancel_key, sizeof(int32));
}