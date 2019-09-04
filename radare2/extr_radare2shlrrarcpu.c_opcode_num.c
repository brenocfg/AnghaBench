#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* opcodes ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static inline int opcode_num (const char *s) {
	int i;
	for (i=0; opcodes[i].name; i++)
		if (!strcmp (s, opcodes[i].name))
			return i;
	return -1;
}