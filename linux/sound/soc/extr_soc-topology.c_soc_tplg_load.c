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
struct soc_tplg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  soc_tplg_complete (struct soc_tplg*) ; 
 int soc_tplg_process_headers (struct soc_tplg*) ; 

__attribute__((used)) static int soc_tplg_load(struct soc_tplg *tplg)
{
	int ret;

	ret = soc_tplg_process_headers(tplg);
	if (ret == 0)
		soc_tplg_complete(tplg);

	return ret;
}