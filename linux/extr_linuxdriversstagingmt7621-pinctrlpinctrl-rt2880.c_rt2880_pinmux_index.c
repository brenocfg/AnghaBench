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
struct rt2880_priv {int group_count; int func_count; int /*<<< orphan*/  dev; struct rt2880_pmx_group* groups; struct rt2880_pmx_func** func; scalar_t__* group_names; } ;
struct rt2880_pmx_group {int func_count; struct rt2880_pmx_func* func; scalar_t__ name; } ;
struct rt2880_pmx_func {int* groups; int group_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rt2880_pmx_func gpio_func ; 

__attribute__((used)) static int rt2880_pinmux_index(struct rt2880_priv *p)
{
	struct rt2880_pmx_func **f;
	struct rt2880_pmx_group *mux = p->groups;
	int i, j, c = 0;

	/* count the mux functions */
	while (mux->name) {
		p->group_count++;
		mux++;
	}

	/* allocate the group names array needed by the gpio function */
	p->group_names = devm_kcalloc(p->dev, p->group_count,
				      sizeof(char *), GFP_KERNEL);
	if (!p->group_names)
		return -1;

	for (i = 0; i < p->group_count; i++) {
		p->group_names[i] = p->groups[i].name;
		p->func_count += p->groups[i].func_count;
	}

	/* we have a dummy function[0] for gpio */
	p->func_count++;

	/* allocate our function and group mapping index buffers */
	f = p->func = devm_kcalloc(p->dev,
				   p->func_count,
				   sizeof(struct rt2880_pmx_func),
				   GFP_KERNEL);
	gpio_func.groups = devm_kcalloc(p->dev, p->group_count, sizeof(int),
					GFP_KERNEL);
	if (!f || !gpio_func.groups)
		return -1;

	/* add a backpointer to the function so it knows its group */
	gpio_func.group_count = p->group_count;
	for (i = 0; i < gpio_func.group_count; i++)
		gpio_func.groups[i] = i;

	f[c] = &gpio_func;
	c++;

	/* add remaining functions */
	for (i = 0; i < p->group_count; i++) {
		for (j = 0; j < p->groups[i].func_count; j++) {
			f[c] = &p->groups[i].func[j];
			f[c]->groups = devm_kzalloc(p->dev, sizeof(int),
						    GFP_KERNEL);
			f[c]->groups[0] = i;
			f[c]->group_count = 1;
			c++;
		}
	}
	return 0;
}