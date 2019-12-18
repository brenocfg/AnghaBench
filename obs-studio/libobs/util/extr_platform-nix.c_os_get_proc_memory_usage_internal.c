#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dirty_pages; int /*<<< orphan*/  data; int /*<<< orphan*/  library; int /*<<< orphan*/  text; int /*<<< orphan*/  share_pages; int /*<<< orphan*/  resident_size; int /*<<< orphan*/  virtual_size; } ;
typedef  TYPE_1__ statm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool os_get_proc_memory_usage_internal(statm_t *statm)
{
	const char *statm_path = "/proc/self/statm";

	FILE *f = fopen(statm_path, "r");
	if (!f)
		return false;

	if (fscanf(f, "%lu %lu %lu %lu %lu %lu %lu", &statm->virtual_size,
		   &statm->resident_size, &statm->share_pages, &statm->text,
		   &statm->library, &statm->data, &statm->dirty_pages) != 7) {
		fclose(f);
		return false;
	}

	fclose(f);
	return true;
}