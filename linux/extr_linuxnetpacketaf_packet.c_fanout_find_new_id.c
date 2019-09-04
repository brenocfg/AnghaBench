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
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ __fanout_id_is_free (struct sock*,scalar_t__) ; 
 scalar_t__ fanout_next_id ; 

__attribute__((used)) static bool fanout_find_new_id(struct sock *sk, u16 *new_id)
{
	u16 id = fanout_next_id;

	do {
		if (__fanout_id_is_free(sk, id)) {
			*new_id = id;
			fanout_next_id = id + 1;
			return true;
		}

		id++;
	} while (id != fanout_next_id);

	return false;
}