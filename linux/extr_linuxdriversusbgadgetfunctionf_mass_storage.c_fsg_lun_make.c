#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct fsg_opts {int /*<<< orphan*/  lock; TYPE_2__* common; scalar_t__ refcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  ci_name; } ;
struct config_group {TYPE_1__ cg_item; } ;
struct fsg_lun_opts {size_t lun_id; struct config_group group; scalar_t__ lun; } ;
struct fsg_lun_config {int removable; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_4__ {scalar_t__* luns; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 struct config_group* ERR_PTR (int) ; 
 size_t FSG_MAX_LUNS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t array_index_nospec (size_t,size_t) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 int fsg_common_create_lun (TYPE_2__*,struct fsg_lun_config*,size_t,char const*,char const**) ; 
 int /*<<< orphan*/  fsg_lun_type ; 
 int /*<<< orphan*/  kfree (struct fsg_lun_opts*) ; 
 int kstrtou8 (char*,int /*<<< orphan*/ ,size_t*) ; 
 struct fsg_lun_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fsg_lun_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* strchr (char const*,char) ; 
 struct fsg_opts* to_fsg_opts (TYPE_1__*) ; 

__attribute__((used)) static struct config_group *fsg_lun_make(struct config_group *group,
					 const char *name)
{
	struct fsg_lun_opts *opts;
	struct fsg_opts *fsg_opts;
	struct fsg_lun_config config;
	char *num_str;
	u8 num;
	int ret;

	num_str = strchr(name, '.');
	if (!num_str) {
		pr_err("Unable to locate . in LUN.NUMBER\n");
		return ERR_PTR(-EINVAL);
	}
	num_str++;

	ret = kstrtou8(num_str, 0, &num);
	if (ret)
		return ERR_PTR(ret);

	fsg_opts = to_fsg_opts(&group->cg_item);
	if (num >= FSG_MAX_LUNS)
		return ERR_PTR(-ERANGE);
	num = array_index_nospec(num, FSG_MAX_LUNS);

	mutex_lock(&fsg_opts->lock);
	if (fsg_opts->refcnt || fsg_opts->common->luns[num]) {
		ret = -EBUSY;
		goto out;
	}

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts) {
		ret = -ENOMEM;
		goto out;
	}

	memset(&config, 0, sizeof(config));
	config.removable = true;

	ret = fsg_common_create_lun(fsg_opts->common, &config, num, name,
				    (const char **)&group->cg_item.ci_name);
	if (ret) {
		kfree(opts);
		goto out;
	}
	opts->lun = fsg_opts->common->luns[num];
	opts->lun_id = num;
	mutex_unlock(&fsg_opts->lock);

	config_group_init_type_name(&opts->group, name, &fsg_lun_type);

	return &opts->group;
out:
	mutex_unlock(&fsg_opts->lock);
	return ERR_PTR(ret);
}