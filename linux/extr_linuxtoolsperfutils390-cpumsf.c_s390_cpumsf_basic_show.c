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
struct hws_basic_entry {int def; int /*<<< orphan*/  gpp; int /*<<< orphan*/  hpp; int /*<<< orphan*/  CL; int /*<<< orphan*/  ia; int /*<<< orphan*/  prim_asn; int /*<<< orphan*/  AS; scalar_t__ I; scalar_t__ P; scalar_t__ W; scalar_t__ T; int /*<<< orphan*/  U; } ;

/* Variables and functions */
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,size_t,int,int /*<<< orphan*/ ,char,char,char,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static bool s390_cpumsf_basic_show(const char *color, size_t pos,
				   struct hws_basic_entry *basic)
{
	if (basic->def != 1) {
		pr_err("Invalid AUX trace basic entry [%#08zx]\n", pos);
		return false;
	}
	color_fprintf(stdout, color, "    [%#08zx] Basic   Def:%04x Inst:%#04x"
		      " %c%c%c%c AS:%d ASN:%#04x IA:%#018llx\n"
		      "\t\tCL:%d HPP:%#018llx GPP:%#018llx\n",
		      pos, basic->def, basic->U,
		      basic->T ? 'T' : ' ',
		      basic->W ? 'W' : ' ',
		      basic->P ? 'P' : ' ',
		      basic->I ? 'I' : ' ',
		      basic->AS, basic->prim_asn, basic->ia, basic->CL,
		      basic->hpp, basic->gpp);
	return true;
}