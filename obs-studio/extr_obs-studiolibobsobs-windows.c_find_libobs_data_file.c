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
struct dstr {char* array; } ;

/* Variables and functions */
 scalar_t__ check_path (char const*,char*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 

char *find_libobs_data_file(const char *file)
{
	struct dstr path;
	dstr_init(&path);

	if (check_path(file, "data/libobs/", &path))
		return path.array;

	if (check_path(file, "../../data/libobs/", &path))
		return path.array;

	dstr_free(&path);
	return NULL;
}