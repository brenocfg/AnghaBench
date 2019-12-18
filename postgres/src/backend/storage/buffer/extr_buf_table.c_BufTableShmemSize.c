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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  BufferLookupEnt ;

/* Variables and functions */
 int /*<<< orphan*/  hash_estimate_size (int,int) ; 

Size
BufTableShmemSize(int size)
{
	return hash_estimate_size(size, sizeof(BufferLookupEnt));
}