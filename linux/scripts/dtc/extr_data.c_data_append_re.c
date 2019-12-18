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
typedef  int /*<<< orphan*/  uint64_t ;
struct fdt_reserve_entry {void* size; void* address; } ;
struct data {int dummy; } ;
typedef  int /*<<< orphan*/  re ;

/* Variables and functions */
 void* cpu_to_fdt64 (int /*<<< orphan*/ ) ; 
 struct data data_append_data (struct data,struct fdt_reserve_entry*,int) ; 

struct data data_append_re(struct data d, uint64_t address, uint64_t size)
{
	struct fdt_reserve_entry re;

	re.address = cpu_to_fdt64(address);
	re.size = cpu_to_fdt64(size);

	return data_append_data(d, &re, sizeof(re));
}