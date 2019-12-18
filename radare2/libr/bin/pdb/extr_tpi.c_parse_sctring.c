#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ SCString ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_READ (unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  init_scstring (TYPE_1__*,unsigned int,char*) ; 

int parse_sctring(SCString *sctr, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len) {
	unsigned int c = 0;
	sctr->name = NULL;
	sctr->size = 0;
	while (*leaf_data) {
		CAN_READ((*read_bytes + c), 1, len);
		c++;
		leaf_data++;
	}
	CAN_READ(*read_bytes, 1, len);
	leaf_data += 1;
	(*read_bytes) += (c + 1);

	init_scstring (sctr, c + 1, (char *)leaf_data - (c + 1));
	return 1;
}