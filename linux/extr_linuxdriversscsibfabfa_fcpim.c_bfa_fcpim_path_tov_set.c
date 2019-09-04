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
typedef  int u16 ;
struct bfa_s {int dummy; } ;
struct bfa_fcpim_s {int path_tov; } ;

/* Variables and functions */
 struct bfa_fcpim_s* BFA_FCPIM (struct bfa_s*) ; 
 int BFA_FCPIM_PATHTOV_MAX ; 

void
bfa_fcpim_path_tov_set(struct bfa_s *bfa, u16 path_tov)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);

	fcpim->path_tov = path_tov * 1000;
	if (fcpim->path_tov > BFA_FCPIM_PATHTOV_MAX)
		fcpim->path_tov = BFA_FCPIM_PATHTOV_MAX;
}