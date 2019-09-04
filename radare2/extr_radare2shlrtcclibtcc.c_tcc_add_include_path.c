#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nb_include_paths; int /*<<< orphan*/  include_paths; } ;
typedef  TYPE_1__ TCCState ;

/* Variables and functions */
 int /*<<< orphan*/  tcc_split_path (TYPE_1__*,void***,int /*<<< orphan*/ *,char const*) ; 

int tcc_add_include_path(TCCState *s, const char *pathname)
{
	tcc_split_path (s, (void ***) &s->include_paths, &s->nb_include_paths, pathname);
	return 0;
}