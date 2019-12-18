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
typedef  int u_max ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct type_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ get_signed_val (struct type_descriptor*,void*) ; 
 int get_unsigned_val (struct type_descriptor*,void*) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,...) ; 
 int type_bit_width (struct type_descriptor*) ; 
 scalar_t__ type_is_int (struct type_descriptor*) ; 
 scalar_t__ type_is_signed (struct type_descriptor*) ; 

__attribute__((used)) static void val_to_string(char *str, size_t size, struct type_descriptor *type,
			void *value)
{
	if (type_is_int(type)) {
		if (type_bit_width(type) == 128) {
#if defined(CONFIG_ARCH_SUPPORTS_INT128) && defined(__SIZEOF_INT128__)
			u_max val = get_unsigned_val(type, value);

			scnprintf(str, size, "0x%08x%08x%08x%08x",
				(u32)(val >> 96),
				(u32)(val >> 64),
				(u32)(val >> 32),
				(u32)(val));
#else
			WARN_ON(1);
#endif
		} else if (type_is_signed(type)) {
			scnprintf(str, size, "%lld",
				(s64)get_signed_val(type, value));
		} else {
			scnprintf(str, size, "%llu",
				(u64)get_unsigned_val(type, value));
		}
	}
}