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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline ino_t
cifs_uniqueid_to_ino_t(u64 fileid)
{
	if ((sizeof(ino_t)) < (sizeof(u64)))
		return (ino_t)hash_64(fileid, (sizeof(ino_t) * 8) - 1) + 1;

	return (ino_t)fileid;

}