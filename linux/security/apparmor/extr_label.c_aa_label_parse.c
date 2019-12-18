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
struct aa_label {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct aa_label* aa_label_strn_parse (struct aa_label*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct aa_label *aa_label_parse(struct aa_label *base, const char *str,
				gfp_t gfp, bool create, bool force_stack)
{
	return aa_label_strn_parse(base, str, strlen(str), gfp, create,
				   force_stack);
}