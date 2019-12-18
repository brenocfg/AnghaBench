#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {char* name; TYPE_2__* root; scalar_t__ path; } ;
struct TYPE_5__ {char* (* cmdstrf ) (void*,char*,char*,char const*,int /*<<< orphan*/  const*) ;void* core; } ;
struct TYPE_6__ {TYPE_1__ cob; } ;
typedef  TYPE_3__ RFSFile ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 char* stub1 (void*,char*,char*,char const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool __cfg_write(RFSFile *file, ut64 addr, const ut8 *data, int len) {
	const char *a = file->name;
	void *core = file->root->cob.core;
	char *prefix = strdup (file->path + strlen ("/cfg/"));
	char *res = file->root->cob.cmdstrf (core, "e %s.%s=%s", prefix, a, data);
	free (prefix);
	free (res);
	return true;
}