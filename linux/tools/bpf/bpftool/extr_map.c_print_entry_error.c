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
struct bpf_map_info {int key_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprint_hex (int /*<<< orphan*/ ,unsigned char*,int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 

__attribute__((used)) static void print_entry_error(struct bpf_map_info *info, unsigned char *key,
			      const char *error_msg)
{
	int msg_size = strlen(error_msg);
	bool single_line, break_names;

	break_names = info->key_size > 16 || msg_size > 16;
	single_line = info->key_size + msg_size <= 24 && !break_names;

	printf("key:%c", break_names ? '\n' : ' ');
	fprint_hex(stdout, key, info->key_size, " ");

	printf(single_line ? "  " : "\n");

	printf("value:%c%s", break_names ? '\n' : ' ', error_msg);

	printf("\n");
}