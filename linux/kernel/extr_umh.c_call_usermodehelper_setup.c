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
struct subprocess_info {char const* path; char** argv; char** envp; void (* cleanup ) (struct subprocess_info*) ;int (* init ) (struct subprocess_info*,struct cred*) ;void* data; int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 char const* CONFIG_STATIC_USERMODEHELPER_PATH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_usermodehelper_exec_work ; 
 struct subprocess_info* kzalloc (int,int /*<<< orphan*/ ) ; 

struct subprocess_info *call_usermodehelper_setup(const char *path, char **argv,
		char **envp, gfp_t gfp_mask,
		int (*init)(struct subprocess_info *info, struct cred *new),
		void (*cleanup)(struct subprocess_info *info),
		void *data)
{
	struct subprocess_info *sub_info;
	sub_info = kzalloc(sizeof(struct subprocess_info), gfp_mask);
	if (!sub_info)
		goto out;

	INIT_WORK(&sub_info->work, call_usermodehelper_exec_work);

#ifdef CONFIG_STATIC_USERMODEHELPER
	sub_info->path = CONFIG_STATIC_USERMODEHELPER_PATH;
#else
	sub_info->path = path;
#endif
	sub_info->argv = argv;
	sub_info->envp = envp;

	sub_info->cleanup = cleanup;
	sub_info->init = init;
	sub_info->data = data;
  out:
	return sub_info;
}