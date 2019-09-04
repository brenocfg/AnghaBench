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
struct ra_renderpass_input {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  inputs ;

/* Variables and functions */
 struct ra_renderpass_input* talloc_memdup (void*,void*,int) ; 
 int /*<<< orphan*/  talloc_strdup (struct ra_renderpass_input*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ra_renderpass_input *dup_inputs(void *ta_parent,
            const struct ra_renderpass_input *inputs, int num_inputs)
{
    struct ra_renderpass_input *res =
        talloc_memdup(ta_parent, (void *)inputs, num_inputs * sizeof(inputs[0]));
    for (int n = 0; n < num_inputs; n++)
        res[n].name = talloc_strdup(res, res[n].name);
    return res;
}