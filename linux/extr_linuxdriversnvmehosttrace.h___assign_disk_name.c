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
struct gendisk {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_NAME_LEN ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __assign_disk_name(char *name, struct gendisk *disk)
{
	if (disk)
		memcpy(name, disk->disk_name, DISK_NAME_LEN);
	else
		memset(name, 0, DISK_NAME_LEN);
}