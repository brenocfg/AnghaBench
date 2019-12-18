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
struct stat {int st_mode; } ;
struct perf_data {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFMT ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static bool is_dir(struct perf_data *data)
{
	struct stat st;

	if (stat(data->path, &st))
		return false;

	return (st.st_mode & S_IFMT) == S_IFDIR;
}