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
typedef  int /*<<< orphan*/  u8 ;
struct michael_mic {void* k1; void* k0; } ;

/* Variables and functions */
 void* get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  michael_clear (struct michael_mic*) ; 

__attribute__((used)) static void michael_init(struct michael_mic *mic, u8 *key)
{
	// Set the key
	mic->k0 = get_unaligned_le32(key);
	mic->k1 = get_unaligned_le32(key + 4);

	//clear();
	michael_clear(mic);
}