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
struct vc_data {size_t vc_y; unsigned int vc_x; unsigned int vc_cols; } ;
struct uni_screen {int /*<<< orphan*/ ** lines; } ;
typedef  int /*<<< orphan*/  char32_t ;

/* Variables and functions */
 struct uni_screen* get_vc_uniscr (struct vc_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ *,char,unsigned int) ; 

__attribute__((used)) static void vc_uniscr_delete(struct vc_data *vc, unsigned int nr)
{
	struct uni_screen *uniscr = get_vc_uniscr(vc);

	if (uniscr) {
		char32_t *ln = uniscr->lines[vc->vc_y];
		unsigned int x = vc->vc_x, cols = vc->vc_cols;

		memcpy(&ln[x], &ln[x + nr], (cols - x - nr) * sizeof(*ln));
		memset32(&ln[cols - nr], ' ', nr);
	}
}