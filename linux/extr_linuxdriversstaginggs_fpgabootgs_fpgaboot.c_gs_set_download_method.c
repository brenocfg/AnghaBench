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
struct fpgaimage {int /*<<< orphan*/  dmethod; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_systemmap ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int gs_set_download_method(struct fpgaimage *fimage)
{
	pr_info("set program method\n");

	fimage->dmethod = m_systemmap;

	pr_info("systemmap program method\n");

	return 0;
}