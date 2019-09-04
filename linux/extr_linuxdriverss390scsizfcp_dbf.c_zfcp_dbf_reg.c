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
struct debug_info {int dummy; } ;
typedef  struct debug_info debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbflevel ; 
 int /*<<< orphan*/  debug_hex_ascii_view ; 
 struct debug_info* debug_register (char const*,int,int,int) ; 
 int /*<<< orphan*/  debug_register_view (struct debug_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (struct debug_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static debug_info_t *zfcp_dbf_reg(const char *name, int size, int rec_size)
{
	struct debug_info *d;

	d = debug_register(name, size, 1, rec_size);
	if (!d)
		return NULL;

	debug_register_view(d, &debug_hex_ascii_view);
	debug_set_level(d, dbflevel);

	return d;
}