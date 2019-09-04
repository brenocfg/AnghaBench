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
struct bpf_object {int /*<<< orphan*/  (* clear_priv ) (struct bpf_object*,void*) ;void* priv; } ;
typedef  int /*<<< orphan*/  (* bpf_object_clear_priv_t ) (struct bpf_object*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct bpf_object*,void*) ; 

int bpf_object__set_priv(struct bpf_object *obj, void *priv,
			 bpf_object_clear_priv_t clear_priv)
{
	if (obj->priv && obj->clear_priv)
		obj->clear_priv(obj, obj->priv);

	obj->priv = priv;
	obj->clear_priv = clear_priv;
	return 0;
}