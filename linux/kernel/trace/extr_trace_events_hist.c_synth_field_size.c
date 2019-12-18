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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ synth_field_is_string (char*) ; 
 int synth_field_string_size (char*) ; 

__attribute__((used)) static int synth_field_size(char *type)
{
	int size = 0;

	if (strcmp(type, "s64") == 0)
		size = sizeof(s64);
	else if (strcmp(type, "u64") == 0)
		size = sizeof(u64);
	else if (strcmp(type, "s32") == 0)
		size = sizeof(s32);
	else if (strcmp(type, "u32") == 0)
		size = sizeof(u32);
	else if (strcmp(type, "s16") == 0)
		size = sizeof(s16);
	else if (strcmp(type, "u16") == 0)
		size = sizeof(u16);
	else if (strcmp(type, "s8") == 0)
		size = sizeof(s8);
	else if (strcmp(type, "u8") == 0)
		size = sizeof(u8);
	else if (strcmp(type, "char") == 0)
		size = sizeof(char);
	else if (strcmp(type, "unsigned char") == 0)
		size = sizeof(unsigned char);
	else if (strcmp(type, "int") == 0)
		size = sizeof(int);
	else if (strcmp(type, "unsigned int") == 0)
		size = sizeof(unsigned int);
	else if (strcmp(type, "long") == 0)
		size = sizeof(long);
	else if (strcmp(type, "unsigned long") == 0)
		size = sizeof(unsigned long);
	else if (strcmp(type, "pid_t") == 0)
		size = sizeof(pid_t);
	else if (strcmp(type, "gfp_t") == 0)
		size = sizeof(gfp_t);
	else if (synth_field_is_string(type))
		size = synth_field_string_size(type);

	return size;
}