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
typedef  scalar_t__ u8 ;
struct ccid_operations {scalar_t__ const ccid_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ccid_operations**) ; 
 struct ccid_operations** ccids ; 

__attribute__((used)) static struct ccid_operations *ccid_by_number(const u8 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ccids); i++)
		if (ccids[i]->ccid_id == id)
			return ccids[i];
	return NULL;
}