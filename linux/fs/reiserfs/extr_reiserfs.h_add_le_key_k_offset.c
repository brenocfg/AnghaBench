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
struct reiserfs_key {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ le_key_k_offset (int,struct reiserfs_key*) ; 
 int /*<<< orphan*/  set_le_key_k_offset (int,struct reiserfs_key*,scalar_t__) ; 

__attribute__((used)) static inline void add_le_key_k_offset(int version, struct reiserfs_key *key,
				       loff_t offset)
{
	set_le_key_k_offset(version, key,
			    le_key_k_offset(version, key) + offset);
}