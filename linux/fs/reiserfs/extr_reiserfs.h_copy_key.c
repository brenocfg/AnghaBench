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
 int /*<<< orphan*/  KEY_SIZE ; 
 int /*<<< orphan*/  memcpy (struct reiserfs_key*,struct reiserfs_key const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void copy_key(struct reiserfs_key *to,
			    const struct reiserfs_key *from)
{
	memcpy(to, from, KEY_SIZE);
}