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
struct aa_ns {int dummy; } ;
struct aa_label {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int ENOMEM ; 
 int aa_label_snxprint (char*,int,struct aa_ns*,struct aa_label*,int) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 

int aa_label_asxprint(char **strp, struct aa_ns *ns, struct aa_label *label,
		      int flags, gfp_t gfp)
{
	int size;

	AA_BUG(!strp);
	AA_BUG(!label);

	size = aa_label_snxprint(NULL, 0, ns, label, flags);
	if (size < 0)
		return size;

	*strp = kmalloc(size + 1, gfp);
	if (!*strp)
		return -ENOMEM;
	return aa_label_snxprint(*strp, size + 1, ns, label, flags);
}