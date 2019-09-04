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
struct st_var_header {int /*<<< orphan*/  var_id; } ;
struct st_bits_data {short mask; } ;
struct punc_var_t {size_t value; } ;
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct kobj_attribute {TYPE_1__ attr; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 short* spk_chartab ; 
 struct punc_var_t* spk_get_punc_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spk_punc_info ; 
 struct st_var_header* spk_var_header_by_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t punc_show(struct kobject *kobj, struct kobj_attribute *attr,
			 char *buf)
{
	int i;
	char *cp = buf;
	struct st_var_header *p_header;
	struct punc_var_t *var;
	struct st_bits_data *pb;
	short mask;
	unsigned long flags;

	p_header = spk_var_header_by_name(attr->attr.name);
	if (!p_header) {
		pr_warn("p_header is null, attr->attr.name is %s\n",
			attr->attr.name);
		return -EINVAL;
	}

	var = spk_get_punc_var(p_header->var_id);
	if (!var) {
		pr_warn("var is null, p_header->var_id is %i\n",
			p_header->var_id);
		return -EINVAL;
	}

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	pb = (struct st_bits_data *)&spk_punc_info[var->value];
	mask = pb->mask;
	for (i = 33; i < 128; i++) {
		if (!(spk_chartab[i] & mask))
			continue;
		*cp++ = (char)i;
	}
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	return cp - buf;
}