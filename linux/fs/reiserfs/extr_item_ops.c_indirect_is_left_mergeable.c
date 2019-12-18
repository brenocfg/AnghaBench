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

/* Variables and functions */
 int le_key_k_offset (int,struct reiserfs_key*) ; 
 int le_key_version (struct reiserfs_key*) ; 

__attribute__((used)) static int indirect_is_left_mergeable(struct reiserfs_key *key,
				      unsigned long bsize)
{
	int version = le_key_version(key);
	return (le_key_k_offset(version, key) != 1);
}