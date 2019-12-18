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
typedef  int u32 ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  aa_audit_perm_names (struct audit_buffer*,char const* const*,int) ; 
 int /*<<< orphan*/  aa_perm_mask_to_str (char*,int,char const*,int) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 

void aa_audit_perm_mask(struct audit_buffer *ab, u32 mask, const char *chrs,
			u32 chrsmask, const char * const *names, u32 namesmask)
{
	char str[33];

	audit_log_format(ab, "\"");
	if ((mask & chrsmask) && chrs) {
		aa_perm_mask_to_str(str, sizeof(str), chrs, mask & chrsmask);
		mask &= ~chrsmask;
		audit_log_format(ab, "%s", str);
		if (mask & namesmask)
			audit_log_format(ab, " ");
	}
	if ((mask & namesmask) && names)
		aa_audit_perm_names(ab, names, mask & namesmask);
	audit_log_format(ab, "\"");
}