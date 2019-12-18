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
struct tracepoint_path {struct tracepoint_path* name; struct tracepoint_path* system; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tracepoint_path*) ; 
 char* strchr (char const*,char) ; 
 struct tracepoint_path* strdup (char*) ; 
 struct tracepoint_path* strndup (char const*,int) ; 
 struct tracepoint_path* zalloc (int) ; 
 int /*<<< orphan*/  zfree (struct tracepoint_path**) ; 

struct tracepoint_path *tracepoint_name_to_path(const char *name)
{
	struct tracepoint_path *path = zalloc(sizeof(*path));
	char *str = strchr(name, ':');

	if (path == NULL || str == NULL) {
		free(path);
		return NULL;
	}

	path->system = strndup(name, str - name);
	path->name = strdup(str+1);

	if (path->system == NULL || path->name == NULL) {
		zfree(&path->system);
		zfree(&path->name);
		zfree(&path);
	}

	return path;
}