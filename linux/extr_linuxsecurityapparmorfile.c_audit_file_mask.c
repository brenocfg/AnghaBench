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
typedef  int /*<<< orphan*/  u32 ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  aa_file_perm_chrs ; 
 int /*<<< orphan*/  aa_perm_mask_to_str (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  map_mask_to_chr_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audit_file_mask(struct audit_buffer *ab, u32 mask)
{
	char str[10];

	aa_perm_mask_to_str(str, sizeof(str), aa_file_perm_chrs,
			    map_mask_to_chr_mask(mask));
	audit_log_string(ab, str);
}