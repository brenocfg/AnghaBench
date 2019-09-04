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
struct idset {int num_ssid; int num_id; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 scalar_t__ bitmap_size (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct idset* vmalloc (scalar_t__) ; 

__attribute__((used)) static struct idset *idset_new(int num_ssid, int num_id)
{
	struct idset *set;

	set = vmalloc(sizeof(struct idset) + bitmap_size(num_ssid, num_id));
	if (set) {
		set->num_ssid = num_ssid;
		set->num_id = num_id;
		memset(set->bitmap, 0, bitmap_size(num_ssid, num_id));
	}
	return set;
}