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
typedef  size_t u_int ;
struct patch {size_t begin; scalar_t__ (* patch_func ) (struct ahc_softc*) ;size_t skip_instr; int /*<<< orphan*/  skip_patch; } ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct patch*) ; 
 struct patch* patches ; 
 scalar_t__ stub1 (struct ahc_softc*) ; 

__attribute__((used)) static int
ahc_check_patch(struct ahc_softc *ahc, const struct patch **start_patch,
		u_int start_instr, u_int *skip_addr)
{
	const struct patch *cur_patch;
	const struct patch *last_patch;
	u_int	num_patches;

	num_patches = ARRAY_SIZE(patches);
	last_patch = &patches[num_patches];
	cur_patch = *start_patch;

	while (cur_patch < last_patch && start_instr == cur_patch->begin) {

		if (cur_patch->patch_func(ahc) == 0) {

			/* Start rejecting code */
			*skip_addr = start_instr + cur_patch->skip_instr;
			cur_patch += cur_patch->skip_patch;
		} else {
			/* Accepted this patch.  Advance to the next
			 * one and wait for our intruction pointer to
			 * hit this point.
			 */
			cur_patch++;
		}
	}

	*start_patch = cur_patch;
	if (start_instr < *skip_addr)
		/* Still skipping */
		return (0);

	return (1);
}