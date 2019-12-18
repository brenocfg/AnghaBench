#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  btf_func; } ;
struct bpf_object {int /*<<< orphan*/ * btf_ext; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  btf_ext__free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpf_object__sanitize_btf_ext(struct bpf_object *obj)
{
	if (!obj->btf_ext)
		return;

	if (!obj->caps.btf_func) {
		btf_ext__free(obj->btf_ext);
		obj->btf_ext = NULL;
	}
}