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
struct cpu_key {int key_length; } ;

/* Variables and functions */
 int comp_short_keys (struct reiserfs_key const*,struct cpu_key const*) ; 
 scalar_t__ cpu_key_k_offset (struct cpu_key const*) ; 
 scalar_t__ cpu_key_k_type (struct cpu_key const*) ; 
 scalar_t__ le_key_k_offset (int /*<<< orphan*/ ,struct reiserfs_key const*) ; 
 scalar_t__ le_key_k_type (int /*<<< orphan*/ ,struct reiserfs_key const*) ; 
 int /*<<< orphan*/  le_key_version (struct reiserfs_key const*) ; 

__attribute__((used)) static inline int comp_keys(const struct reiserfs_key *le_key,
			    const struct cpu_key *cpu_key)
{
	int retval;

	retval = comp_short_keys(le_key, cpu_key);
	if (retval)
		return retval;
	if (le_key_k_offset(le_key_version(le_key), le_key) <
	    cpu_key_k_offset(cpu_key))
		return -1;
	if (le_key_k_offset(le_key_version(le_key), le_key) >
	    cpu_key_k_offset(cpu_key))
		return 1;

	if (cpu_key->key_length == 3)
		return 0;

	/* this part is needed only when tail conversion is in progress */
	if (le_key_k_type(le_key_version(le_key), le_key) <
	    cpu_key_k_type(cpu_key))
		return -1;

	if (le_key_k_type(le_key_version(le_key), le_key) >
	    cpu_key_k_type(cpu_key))
		return 1;

	return 0;
}