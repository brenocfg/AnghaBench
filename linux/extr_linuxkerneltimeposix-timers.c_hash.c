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
struct signal_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_BITS (int /*<<< orphan*/ ) ; 
 unsigned int hash32_ptr (struct signal_struct*) ; 
 int hash_32 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_timers_hashtable ; 

__attribute__((used)) static int hash(struct signal_struct *sig, unsigned int nr)
{
	return hash_32(hash32_ptr(sig) ^ nr, HASH_BITS(posix_timers_hashtable));
}