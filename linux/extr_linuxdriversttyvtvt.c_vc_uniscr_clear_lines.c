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
struct vc_data {unsigned int vc_cols; } ;
struct uni_screen {int /*<<< orphan*/ * lines; } ;

/* Variables and functions */
 struct uni_screen* get_vc_uniscr (struct vc_data*) ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ ,char,unsigned int) ; 

__attribute__((used)) static void vc_uniscr_clear_lines(struct vc_data *vc, unsigned int y,
				  unsigned int nr)
{
	struct uni_screen *uniscr = get_vc_uniscr(vc);

	if (uniscr) {
		unsigned int cols = vc->vc_cols;

		while (nr--)
			memset32(uniscr->lines[y++], ' ', cols);
	}
}