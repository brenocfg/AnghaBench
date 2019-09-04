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
typedef  scalar_t__ uint32_t ;
struct serializer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  write_data (struct serializer*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  write_var (struct serializer*,scalar_t__) ; 

__attribute__((used)) static bool write_str(struct serializer *s, const char *str)
{
	uint32_t size = (uint32_t)(str ? strlen(str) : 0);

	if (!write_var(s, size))
		return false;
	if (size && !write_data(s, str, size))
		return false;
	return true;
}