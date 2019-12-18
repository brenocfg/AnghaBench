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
struct audit_buffer {int dummy; } ;
struct aa_ns {int dummy; } ;
struct aa_label {scalar_t__ hname; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_DEBUG (char*) ; 
 int aa_label_asxprint (char**,struct aa_ns*,struct aa_label*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_n_hex (struct audit_buffer*,char const*,int) ; 
 int /*<<< orphan*/  audit_log_n_string (struct audit_buffer*,char const*,int) ; 
 scalar_t__ audit_string_contains_control (char const*,int) ; 
 scalar_t__ display_mode (struct aa_ns*,struct aa_label*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  use_label_hname (struct aa_ns*,struct aa_label*,int) ; 

void aa_label_xaudit(struct audit_buffer *ab, struct aa_ns *ns,
		     struct aa_label *label, int flags, gfp_t gfp)
{
	const char *str;
	char *name = NULL;
	int len;

	AA_BUG(!ab);
	AA_BUG(!label);

	if (!use_label_hname(ns, label, flags) ||
	    display_mode(ns, label, flags)) {
		len  = aa_label_asxprint(&name, ns, label, flags, gfp);
		if (len == -1) {
			AA_DEBUG("label print error");
			return;
		}
		str = name;
	} else {
		str = (char *) label->hname;
		len = strlen(str);
	}
	if (audit_string_contains_control(str, len))
		audit_log_n_hex(ab, str, len);
	else
		audit_log_n_string(ab, str, len);

	kfree(name);
}