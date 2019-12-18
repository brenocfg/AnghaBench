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
struct hws_diag_entry {scalar_t__ def; unsigned long long I; } ;

/* Variables and functions */
 scalar_t__ S390_CPUMSF_DIAG_DEF_FIRST ; 
 scalar_t__ be16toh (scalar_t__) ; 
 unsigned long long be64toh (unsigned long long) ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,size_t,scalar_t__,char) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static bool s390_cpumsf_diag_show(const char *color, size_t pos,
				  struct hws_diag_entry *diagp)
{
	struct hws_diag_entry *diag = diagp;
#if __BYTE_ORDER == __LITTLE_ENDIAN
	struct hws_diag_entry local;
	unsigned long long word = be64toh(*(unsigned long long *)diagp);

	local.def = be16toh(diagp->def);
	local.I = word >> 32 & 0x1;
	diag = &local;
#endif
	if (diag->def < S390_CPUMSF_DIAG_DEF_FIRST) {
		pr_err("Invalid AUX trace diagnostic entry [%#08zx]\n", pos);
		return false;
	}
	color_fprintf(stdout, color, "    [%#08zx] Diag    Def:%04x %c\n",
		      pos, diag->def, diag->I ? 'I' : ' ');
	return true;
}