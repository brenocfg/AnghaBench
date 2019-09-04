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
struct list_head {int dummy; } ;
struct dcookie_struct {int /*<<< orphan*/  hash_list; } ;

/* Variables and functions */
 int dcookie_hash (int /*<<< orphan*/ ) ; 
 struct list_head* dcookie_hashtable ; 
 int /*<<< orphan*/  dcookie_value (struct dcookie_struct*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void hash_dcookie(struct dcookie_struct * dcs)
{
	struct list_head * list = dcookie_hashtable + dcookie_hash(dcookie_value(dcs));
	list_add(&dcs->hash_list, list);
}