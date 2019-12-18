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
struct bpf_map_priv {int /*<<< orphan*/  ops_list; } ;
struct bpf_map_op {int /*<<< orphan*/  list; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__INTERNAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct bpf_map_priv*) ; 
 int PTR_ERR (struct bpf_map_priv*) ; 
 char* bpf_map__name (struct bpf_map*) ; 
 struct bpf_map_priv* bpf_map__priv (struct bpf_map*) ; 
 scalar_t__ bpf_map__set_priv (struct bpf_map*,struct bpf_map_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_priv__clear ; 
 int /*<<< orphan*/  free (struct bpf_map_priv*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct bpf_map_priv* zalloc (int) ; 

__attribute__((used)) static int
bpf_map__add_op(struct bpf_map *map, struct bpf_map_op *op)
{
	const char *map_name = bpf_map__name(map);
	struct bpf_map_priv *priv = bpf_map__priv(map);

	if (IS_ERR(priv)) {
		pr_debug("Failed to get private from map %s\n", map_name);
		return PTR_ERR(priv);
	}

	if (!priv) {
		priv = zalloc(sizeof(*priv));
		if (!priv) {
			pr_debug("Not enough memory to alloc map private\n");
			return -ENOMEM;
		}
		INIT_LIST_HEAD(&priv->ops_list);

		if (bpf_map__set_priv(map, priv, bpf_map_priv__clear)) {
			free(priv);
			return -BPF_LOADER_ERRNO__INTERNAL;
		}
	}

	list_add_tail(&op->list, &priv->ops_list);
	return 0;
}