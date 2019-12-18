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

/* Variables and functions */
 int CONN_HASH_SIZE ; 

__attribute__((used)) static inline int nodeid_hash(int nodeid)
{
	return nodeid & (CONN_HASH_SIZE-1);
}