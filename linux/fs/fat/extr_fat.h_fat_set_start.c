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
struct msdos_dir_entry {void* starthi; void* start; } ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static inline void fat_set_start(struct msdos_dir_entry *de, int cluster)
{
	de->start   = cpu_to_le16(cluster);
	de->starthi = cpu_to_le16(cluster >> 16);
}