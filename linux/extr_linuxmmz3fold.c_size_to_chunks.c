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
 size_t CHUNK_SHIFT ; 
 size_t CHUNK_SIZE ; 

__attribute__((used)) static int size_to_chunks(size_t size)
{
	return (size + CHUNK_SIZE - 1) >> CHUNK_SHIFT;
}