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
struct cs_etm_decoder {int /*<<< orphan*/ * dcd_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cs_etm_decoder*) ; 
 int /*<<< orphan*/  ocsd_destroy_dcd_tree (int /*<<< orphan*/ *) ; 

void cs_etm_decoder__free(struct cs_etm_decoder *decoder)
{
	if (!decoder)
		return;

	ocsd_destroy_dcd_tree(decoder->dcd_tree);
	decoder->dcd_tree = NULL;
	free(decoder);
}