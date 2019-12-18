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
struct colormap {scalar_t__ cd; scalar_t__ cdspace; scalar_t__ locolormap; scalar_t__ cmranges; scalar_t__ hicolormap; scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__) ; 

__attribute__((used)) static void
freecm(struct colormap *cm)
{
	cm->magic = 0;
	if (cm->cd != cm->cdspace)
		FREE(cm->cd);
	if (cm->locolormap != NULL)
		FREE(cm->locolormap);
	if (cm->cmranges != NULL)
		FREE(cm->cmranges);
	if (cm->hicolormap != NULL)
		FREE(cm->hicolormap);
}