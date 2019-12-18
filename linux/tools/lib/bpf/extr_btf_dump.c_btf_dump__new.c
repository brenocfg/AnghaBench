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
struct btf_ext {int dummy; } ;
struct btf_dump_opts {int /*<<< orphan*/ * ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctx; } ;
struct btf_dump {int /*<<< orphan*/ * ident_names; int /*<<< orphan*/ * type_names; TYPE_1__ opts; int /*<<< orphan*/  printf_fn; struct btf_ext const* btf_ext; struct btf const* btf; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  btf_dump_printf_fn_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct btf_dump* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btf_dump__free (struct btf_dump*) ; 
 struct btf_dump* calloc (int,int) ; 
 void* hashmap__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str_equal_fn ; 
 int /*<<< orphan*/  str_hash_fn ; 

struct btf_dump *btf_dump__new(const struct btf *btf,
			       const struct btf_ext *btf_ext,
			       const struct btf_dump_opts *opts,
			       btf_dump_printf_fn_t printf_fn)
{
	struct btf_dump *d;
	int err;

	d = calloc(1, sizeof(struct btf_dump));
	if (!d)
		return ERR_PTR(-ENOMEM);

	d->btf = btf;
	d->btf_ext = btf_ext;
	d->printf_fn = printf_fn;
	d->opts.ctx = opts ? opts->ctx : NULL;

	d->type_names = hashmap__new(str_hash_fn, str_equal_fn, NULL);
	if (IS_ERR(d->type_names)) {
		err = PTR_ERR(d->type_names);
		d->type_names = NULL;
		btf_dump__free(d);
		return ERR_PTR(err);
	}
	d->ident_names = hashmap__new(str_hash_fn, str_equal_fn, NULL);
	if (IS_ERR(d->ident_names)) {
		err = PTR_ERR(d->ident_names);
		d->ident_names = NULL;
		btf_dump__free(d);
		return ERR_PTR(err);
	}

	return d;
}