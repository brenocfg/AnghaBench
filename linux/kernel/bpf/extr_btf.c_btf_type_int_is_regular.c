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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct btf_type {int dummy; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_BYTE_MASKED (int) ; 
 int BITS_ROUNDUP_BYTES (int) ; 
 int BTF_INT_BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ BTF_INT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_type_int (struct btf_type const*) ; 

__attribute__((used)) static bool btf_type_int_is_regular(const struct btf_type *t)
{
	u8 nr_bits, nr_bytes;
	u32 int_data;

	int_data = btf_type_int(t);
	nr_bits = BTF_INT_BITS(int_data);
	nr_bytes = BITS_ROUNDUP_BYTES(nr_bits);
	if (BITS_PER_BYTE_MASKED(nr_bits) ||
	    BTF_INT_OFFSET(int_data) ||
	    (nr_bytes != sizeof(u8) && nr_bytes != sizeof(u16) &&
	     nr_bytes != sizeof(u32) && nr_bytes != sizeof(u64) &&
	     nr_bytes != (2 * sizeof(u64)))) {
		return false;
	}

	return true;
}