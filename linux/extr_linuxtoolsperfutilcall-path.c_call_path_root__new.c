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
struct call_path_root {int /*<<< orphan*/  blocks; int /*<<< orphan*/  call_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_path__init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct call_path_root* zalloc (int) ; 

struct call_path_root *call_path_root__new(void)
{
	struct call_path_root *cpr;

	cpr = zalloc(sizeof(struct call_path_root));
	if (!cpr)
		return NULL;
	call_path__init(&cpr->call_path, NULL, NULL, 0, false);
	INIT_LIST_HEAD(&cpr->blocks);
	return cpr;
}